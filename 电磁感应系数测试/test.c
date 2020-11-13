
#include <reg52.h>
#include <stdio.h>
#include <intrins.h>
#include <lcd.h>
sbit ad9850_w_clk    =P2^2;  //P2.2�ڽ�ad9850��w_clk��/PIN7
sbit ad9850_fq_up    =P2^1;  //P2.1�ڽ�ad9850��fq_up��/PIN8
sbit ad9850_rest     =P2^0;  //P2.0�ڽ�ad9850��rest��/PIN12
sbit ad9850_bit_data =P1^7;  //P1.7�ڽ�ad9850��D7��/PIN25
sbit Key1 = P3^1;
sbit Key2 = P3^0;
uchar code table[]="frequent:MHz";
int num = 1000;
//P1Ϊ8λ���ݿ�
//***************************************************//
//              ad9850��λ(����ģʽ)                 //
//---------------------------------------------------//
void ad9850_reset()
{
ad9850_w_clk=0;
ad9850_fq_up=0;
//rest�ź�
ad9850_rest=0;
ad9850_rest=1;
ad9850_rest=0;
}
//***************************************************//
//              ad9850��λ(����ģʽ)                 //
//---------------------------------------------------//
void ad9850_reset_serial()
{
ad9850_w_clk=0;
ad9850_fq_up=0;
//rest�ź�
ad9850_rest=0;
ad9850_rest=1;
ad9850_rest=0;
//w_clk�ź�
ad9850_w_clk=0;
ad9850_w_clk=1;
ad9850_w_clk=0;
//fq_up�ź�
ad9850_fq_up=0;
ad9850_fq_up=1;
ad9850_fq_up=0;
}
//***************************************************//
//          ��ad9850��д����������(����)             //
//---------------------------------------------------//
void ad9850_wr_parrel(unsigned char w0,double frequence)
{
unsigned char w;
long int y;
double x;
//����Ƶ�ʵ�HEXֵ
x=4294967295/125;//�ʺ�125M����
//���ʱ��Ƶ�ʲ�Ϊ180MHZ���޸ĸô���Ƶ��ֵ����λMHz ������
frequence=frequence/1000000;
frequence=frequence*x;
y=frequence;
//дw0����
w=w0;   
P1=w;      //w0
ad9850_w_clk=1;
ad9850_w_clk=0;
//дw1����
w=(y>>24);
P1=w;      //w1
ad9850_w_clk=1;
ad9850_w_clk=0;
//дw2����
w=(y>>16);
P1=w;      //w2
ad9850_w_clk=1;
ad9850_w_clk=0;
//дw3����
w=(y>>8);
P1=w;      //w3
ad9850_w_clk=1;
ad9850_w_clk=0;
//дw4����
w=(y>>=0);
P1=w;      //w4
ad9850_w_clk=1;
ad9850_w_clk=0;
//����ʼ��
ad9850_fq_up=1;
ad9850_fq_up=0;
}
//***************************************************//
//          ��ad9850��д����������(����)             //
//---------------------------------------------------//
void ad9850_wr_serial(unsigned char w0,double frequence)
{
unsigned char i,w;
long int y;
double x;
//����Ƶ�ʵ�HEXֵ
x=4294967295/125;//�ʺ�125M����
//���ʱ��Ƶ�ʲ�Ϊ180MHZ���޸ĸô���Ƶ��ֵ����λMHz  ������
frequence=frequence/1000000;
frequence=frequence*x;
y=frequence;
//дw4����
w=(y>>=0);
for(i=0;i<8;i++)
{
ad9850_bit_data=(w>>i)&0x01;
ad9850_w_clk=1;
ad9850_w_clk=0;
}
//дw3����
w=(y>>8);
for(i=0;i<8;i++)
{
ad9850_bit_data=(w>>i)&0x01;
ad9850_w_clk=1;
ad9850_w_clk=0;
}
//дw2����
w=(y>>16);
for(i=0;i<8;i++)
{
ad9850_bit_data=(w>>i)&0x01;
ad9850_w_clk=1;
ad9850_w_clk=0;
}
//дw1����
w=(y>>24);
for(i=0;i<8;i++)
{
ad9850_bit_data=(w>>i)&0x01;
ad9850_w_clk=1;
ad9850_w_clk=0;
}
//дw0����
w=w0;   
for(i=0;i<8;i++)
{
ad9850_bit_data=(w>>i)&0x01;
ad9850_w_clk=1;
ad9850_w_clk=0;
}
//����ʼ��
ad9850_fq_up=1;
ad9850_fq_up=0;
}
//***************************************************//
//                   ���Գ���1000Hz                  //
//---------------------------------------------------//



//main()
//{
//unsigned int i,m;
//P0=0x00;
//P1=0x00;
//P2=0x00;
//P3=0x00;
////---------------------------------------------------//
////---------------------------------------------------//
////����д1000Hz����
//ad9850_reset_serial();
//for(i=0;i<10;i++)
//{
//m=1000;
//ad9850_wr_serial(0x00,m);
//m=m+100;
//}
////---------------------------------------------------//
//while(1);
//}

void display1st()
{
	uint i;
	lcdWriteCom(0x00+0x80);
	for(i=0;i<15;i++)
	{
	lcdWriteDate(table[i]);
	}
}
//void Display2rd()
//{
//	uint i;
//	lcdWriteCom(0x40+0x80);
//	for(i=0;i<5;i++)
//	{
//		lcdWriteDate(num+0x37);
//	}		
//}
void delay(uint c)
{
	uint a,b;
	for(;c>0;c--)
		for(b=199;b>0;b--)
			for(a=1;a>0;a--);
}
void KeyScan()
{
	if(Key1==0)
	{
		delay(10);
		if(Key1 == 0)
		{
			num += 100;
			while(Key1 == 1);
		}
	}
	if(Key2==0)
	{
		delay(10);
		if(Key2 == 0)
		{
			num -= 100;
			while(Key2 == 1);
		}
	}	
}

main()
{
	lcdInit();
	while(1)
	{
		display1st();
		KeyScan();
		Display2rd();
//		ad9850_reset_serial();
//		ad9850_wr_serial(0x00,num);
	}
}





