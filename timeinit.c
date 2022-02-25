#include<reg52.h>

void initassign()
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
}