#ifndef _STEPMOTER_H
#define	_STEPMOTER_H
#include<reg52.h>

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif
 sbit K1=P3^1;  //反转按键
 sbit K2=P3^0;  //正转按键
 sbit K3=P3^2;  //停止按键
 sbit FMQ=P1^5;  //  蜂鸣器
 void control1(void);
 void beep(void);
 void motor_ccw(void);
 void motor_cw(void);
#endif