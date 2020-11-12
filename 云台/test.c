#include<reg52.h>
#include"stepmoter.h"
#include"server.h"

#define GPIO_KEY P1
sbit key4=P3^3;
uchar K;
uint KeyValue;
void KEY()
{
	if(key4==0)
	{
		delay(10);
		if(key4==0)
		{
			K++;
			if(K>=3)
			K=0;
			while(key4==1);
		}		
	}
	
}
void control1(void)
{
 uchar r;
 uchar N=64;          //因为步进电机是减速步进电机，减速比的1/64 ，
       //所以N=64时，步进电机主轴转一圈
 while(K=1)
 {
   if(P1==0xe0)
   {
    beep();
  for(r=0;r<N;r++)
  {
    motor_ccw();  //电机逆转
    if(P1==0xb0)
    {
     beep();
   break;
    }
  }
   }
   else if(P1==0xd0)
   {
    beep();
        for(r=0;r<N;r++)
  {
    motor_cw();    //电机反转
    if(P1==0xb0)
    {
     beep();
   break;
    }
  }
   }
   else
   P1=0xf0;    //电机停止
 }
} 
void control2()
{
	Init1();
	while(1)
	{
		KeyScan();
	}
} 
void main()
{
	while(1)
	{
		KeyScan();
		control1();
		control2();
	}
}
void KeyScan()	//带返回值的子函数
{
	P1 = 0xf0;//判断哪一列被按下
	if(P1 != 0xf0)
	{
		delay(5);//软件消抖
		if( P1 != 0xf0)
		{
			switch(P1)
			{
				case 0xe0:	KeyValue = 0;	break;
				case 0xd0:	KeyValue = 1;	break;
				case 0xb0:	KeyValue = 2;	break;
				case 0x70:	KeyValue = 3;	break;
			}
			P3 = 0x0f;//判断哪一行被按下
			switch(P1)
			{
				case 0x0e:	KeyValue = KeyValue;	break;
				case 0x0d:	KeyValue += 4;	break;
				case 0x0b:	KeyValue += 8;	break;
				case 0x07:	KeyValue += 12;	break;
			}
			while(P1 != 0x0f);//松手检测
		}			
	}
	P1 = 0xff;//判断独立按键
	if(P1 != 0xff)
	{
		delay(5);//软件消抖
		if( P1 != 0xff)
		{
			switch(P3)
			{
				case 0xfe:	KeyValue = 16;	break;
				case 0xfd:	KeyValue = 17;	break;
				case 0xfb:	KeyValue = 18;	break;
				case 0xf7:	KeyValue = 19;	break;
			}
			while(P1 != 0xff);//松手检测
		}	
	}	
}
