#ifndef _SERVER_H
#define	_SERVER_H
#include<reg52.h>

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif

sbit PWM=P3^5;
sbit key1=P3^1;
sbit key2=P3^0;
void control2();
void delay(uint xms);
void KeyScan();
void Init1();
#endif