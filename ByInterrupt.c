#include<reg52.h>
#include"timeinit.h"
#define uint unsigned int
#define uchar unsigned char

sbit N1=P2^3;	//N是数码管位数
sbit N2=P2^4;
sbit N3=P2^5;
sbit N4=P2^6;

uchar a[]={0x05,0x7d,0x46,0x54,0x3c,0x94,0x84,0x5d,0x04,0x14};//数码管"0~9"字符
uchar b=0x01;//数码管"0."字符
void delay(uint xms);	//延迟函数，延迟xms毫秒
uint m,num,i,n=0;
void decimal(uint d);	//负责显示小数部分
void integer(uint z);	//负责显示整数部分
void main()
{
	TMOD=0x01;
	initassign();
	EA=1;
	ET0=1;
	TR0=1;
/*	for(m=0;m<=9;m++)		//小数部分
	for(n=100;n>0;n--)
	decimal(m);
	
	for(m=1;m<=9999;m++)	//整数部分
	for(n=25;n>0;n--)
	integer(m);*/
	while(1)
	{
		if(num==20)			//延迟1秒
			{
				num=0;
				m++;
			}
		if(m<=9)
			{
				decimal(m);
			}
		else if(m<=9999)
			{
				n++;
				for(i=0;i<5;i++)
				integer(n);
			}
	}
}

void T0_time()interrupt 1
{
	initassign();
	num++;
}
void delay(uint xms)
{
	uint i;
	for(;xms>0;xms--)
	for(i=110;i>0;i--);
}

void decimal(uint d)
{				//显示小数部分
	N3=0;
	P0=b;		//第三位始终为"0."
	delay(5);
	N3=1;
	N4=0;
	P0=a[d];	//第四位是输入的实参
	delay(5);
	N4=1;
}

void integer(uint z)
{
	uint p,q,x,y;
	void single(uint k);
	void ten(uint k);
	void hundred(uint k);
	void thousand(uint k);
	p=z/1000;		//p为千位数
	q=z%1000/100;	//q为百位数
	x=z%100/10;		//x为十位数
	y=z%10;			//y为个位数
	
	//让数字前面为0的不显示，并且对于不同位数提供不同延时
	//该过程为控速过程，延时过长会导致灯光闪烁不稳定，过短显示速度过快
	if(p!=0)
	{single(y);ten(x);hundred(q);thousand(p);delay(12);}
	else if(q!=0)
	{single(y);ten(x);hundred(q);delay(12);}
	else if(x!=0)
	{single(y);ten(x);delay(20);}
	else
	{single(y);single(y);delay(12);}
}

void single(uint k)	//只显示第四位数
{
	N4=0;
	P0=a[k];
	delay(1);
	N4=1;
}
void ten(uint k)		//只显示第三位数
{
	N3=0;
	P0=a[k];
	delay(1);
	N3=1;
}
void hundred(uint k)	//只显示第二位数
{
	N2=0;
	P0=a[k];
	delay(1);
	N2=1;
}
void thousand(uint k)//只显示第一位数
{
	N1=0;
	P0=a[k];
	delay(1);
	N1=1;
}
