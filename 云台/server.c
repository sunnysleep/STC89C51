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
	TMOD=0x01;			  //��ʱ��0��������ʽ1
	TH0=0xff;
	TL0=0x06;			 //12MHZʱ 250us --> 0.25ms
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
				T=1;		  //��T=1ʱ����������10�Σ�ʹPWM������2.5ms
				while(key1==1);
		}
	}
	if(key2==0)
	{
		delay(10);
		if(key2==0)
		{
			T=9;			  //��T=9����������2�Σ�����PWM��Ϊ0.5ms
			while(key2==1);				
		}
	}

}

void Timer0()interrupt 1
{
	TH0=0xff;
	TL0=0x06;
	T++;				  //ÿ������0.25msʱT+1
	if(T<=10)			  //0.25ms*10=2.5ms  -->  2.5ms��Ϊ�ߵ�ƽ
	{
		PWM=1;	
	}
	else if(T>10&&T<80000)		  //����Ϊ�͵�ƽ  -->  ��ʱ��0.25ms*80000=20ms
	{PWM=0;}
	else if(T==80000)		  //���������㣬��֤����Ϊ20ms
	T=0;
}
