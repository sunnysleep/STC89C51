#ifndef __LCD_H_
#define __LCD_H_

//#define LCD1602_4PINS

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif

#define lcd_Datepins P0	   //P0为数据总线
sbit lcd_rw=P2^5;
sbit lcd_rs=P2^6;
sbit lcd_e=P2^7;
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;

void lcd_delayms(uint c);
void lcdWriteCom(uchar com);
void lcdWriteDate(uchar date);
void lcdInit();
#endif