#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit N1=P2^3;	//N�������λ��
sbit N2=P2^4;
sbit N3=P2^5;
sbit N4=P2^6;

uchar a[]={0x05,0x7d,0x46,0x54,0x3c,0x94,0x84,0x5d,0x04,0x14};//�����"0~9"�ַ�
uchar b=0x01;//�����"0."�ַ�
void delay(uint xms);	//�ӳٺ������ӳ�xms����

void main()
{
	void decimal(uint d);	//������ʾС������
	void integer(uint z);	//������ʾ��������
	uint m,n;
	
	for(m=0;m<=9;m++)		//С������
	for(n=100;n>0;n--)
	decimal(m);
	
	for(m=1;m<=9999;m++)	//��������
	for(n=25;n>0;n--)
	integer(m);
}

void delay(uint xms)
{
	uint i;
	for(;xms>0;xms--)
	for(i=110;i>0;i--);
}

void decimal(uint d)
{				//��ʾС������
	N3=0;
	P0=b;		//����λʼ��Ϊ"0."
	delay(5);
	N3=1;
	N4=0;
	P0=a[d];	//����λ�������ʵ��
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
	p=z/1000;		//pΪǧλ��
	q=z%1000/100;	//qΪ��λ��
	x=z%100/10;		//xΪʮλ��
	y=z%10;			//yΪ��λ��
	
	//������ǰ��Ϊ0�Ĳ���ʾ�����Ҷ��ڲ�ͬλ���ṩ��ͬ��ʱ
	//�ù���Ϊ���ٹ��̣���ʱ�����ᵼ�µƹ���˸���ȶ���������ʾ�ٶȹ���
	if(p!=0)
	{single(y);ten(x);hundred(q);thousand(p);delay(12);}
	else if(q!=0)
	{single(y);ten(x);hundred(q);delay(12);}
	else if(x!=0)
	{single(y);ten(x);delay(20);}
	else
	{single(y);delay(12);single(y);delay(12);}
}

void single(uint k)	//ֻ��ʾ����λ��
{
	N4=0;
	P0=a[k];
	delay(1);
	N4=1;
}
void ten(uint k)		//ֻ��ʾ����λ��
{
	N3=0;
	P0=a[k];
	delay(1);
	N3=1;
}
void hundred(uint k)	//ֻ��ʾ�ڶ�λ��
{
	N2=0;
	P0=a[k];
	delay(1);
	N2=1;
}
void thousand(uint k)//ֻ��ʾ��һλ��
{
	N1=0;
	P0=a[k];
	delay(1);
	N1=1;
}