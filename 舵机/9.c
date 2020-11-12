#include<reg52.h>
#define nchar unsigned char
#define uint unsigned int

sbit PWM=P1^0;
sbit key1=P3^1;
sbit key2=P3^0;

uint count;
uint corner;
void delay(uint xms)
{
	uint j,k;
	for(j=xms;j>0;j--)
		for(k=125;k>0;k--);
}
void Init()
{
	TMOD=0x01;			  //定时器0，工作方式1
	TH0=0xfe;
	TL0=0x33;			 //11MHZ时0.5ms
	IE=0x82;
//	EA=1;
//	ET0=1;
	TR0=1;
}
void KeyScan()
{
	if(key1==0)
	{
		delay(10);
		if(key1==0)
		{
			corner++;
			count=0;
			if(corner==6)
				corner=5;
				while(!key1);
		}
	}
	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			corner--;
			count=0;
			if(corner==0)
				corner=1;
				while(!key2);
		}
	}
}
void main()
{
	corner=1;
	count=0;
	Init();
	while(1)
	{
		KeyScan();

	}
}
void Timer0()interrupt 1
{
	TH0=0xfe;
	TL0=0x33;
	if(count<corner)
		PWM=1;
	else
		PWM=0;
		count=count+1;
		count=count%40;	
}
