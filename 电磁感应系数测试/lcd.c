#include "lcd.h"

void lcd_delayms(uint c)
{
	uint a,b;
	for(;c>0;c--)
		for(b=199;b>0;b--)
			for(a=1;a>0;a--);
}
#ifndef  LCD1602_4PINS
void lcdWriteCom(uchar com)		  //д���������
{
	lcd_rs=0;
	lcd_e=0;
	lcd_rw=0;

	P0=com;
	lcd_delayms(1);

	lcd_e=1;
	lcd_delayms(5);
	lcd_e=0;
}
#else
void lcdWriteCom(uchar com)		  //д���������
{
	lcd_rs=0;
	lcd_e=0;
	lcd_rw=0;

	P0=com;
	lcd_delayms(1);

	lcd_e=1;
	lcd_delayms(5);
	lcd_e=0;

	P0=com<<4;
	lcd_delayms(1);

	lcd_e=1;
	lcd_delayms(5);
	lcd_e=0;
}
#endif

#ifndef  LCD1602_4PINS 
void lcdWriteDate(uchar date)	  //д������
{
	lcd_rs=1;
	lcd_e=0;
	lcd_rw=0;

	P0=date;
	lcd_delayms(1);

	lcd_e=1;
	lcd_delayms(5);
	lcd_e=0;
}
#else
void lcdWriteDate(uchar date)	//д������
{
	lcd_rs=1;
	lcd_e=0;
	lcd_rw=0;

	P0=date;
	lcd_delayms(1);

	lcd_e=1;
	lcd=delayms(5);
	lcd_e=0;

	P0=date<<4;
	lcd_delayms(1);

	lcd_e=1;
	lcd=delayms(5);
	lcd_e=0;
}
#endif

#ifndef	 LCD1602_4PINS
void lcdInit()
{
	lcdWriteCom(0x38);	//����ʾ
	lcdWriteCom(0x0c);	//����ʾ�������
	lcdWriteCom(0x06);	//ָ���1
	lcdWriteCom(0x01);	//����
	lcdWriteCom(0x80);	//����ָ�����
}
#else
void lcdInit()
{
	lcdWriteCom(0x32);	 //8λ����ת��4λ����
	lcdWriteCom(0x28);
	lcdWriteCom(0x0c);
	lcdWriteCom(0x06);
	lcdWriteCom(0x01);
	lcdWriteCom(0x80);
}
#endif