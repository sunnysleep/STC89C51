#include"server.h"
uint T;
uint count;
void delay(uint xms)
{
	uint j,k;
	for(j=xms;j>0;j--)
		for(k=125;k>0;k--);
}
void Init1()
{
	TMOD=0x01;			  //定时器0，工作方式1
	TH0=0xff;
	TL0=0x06;			 //12MHZ时 250us --> 0.25ms
	EA=1;
	ET0=1;
	TR0=1;
}
void KeyScan()
{
	if(key1==0)
	{
		delay(10);
		if(key1==0)
		{
				T=1;		  //从T=1时计数，计数10次，使PWM波满足2.5ms
				while(key1==1);
		}
	}
	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			T=9;			  //从T=9计数，计数2次，满足PWM波为0.5ms
			while(key2==1);				
		}
	}

}

void Timer0()interrupt 1
{
	TH0=0xff;
	TL0=0x06;
	T++;				  //每当计数0.25ms时T+1
	if(T<=10)			  //0.25ms*10=2.5ms  -->  2.5ms内为高电平
	{
		PWM=1;	
	}
	else if(T>10&&T<80000)		  //其余为低电平  -->  总时长0.25ms*80000=20ms
	{PWM=0;}
	else if(T==80000)		  //计满后清零，保证周期为20ms
	T=0;
}
