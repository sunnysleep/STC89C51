#include<stepmoter.h>
#include<intrins.h>
 
 uchar code CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表
 uchar code CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表

void delaynms(uint aa)
{
  uchar bb;
  while(aa--)
  {
   for(bb=0;bb<115;bb++)     //1ms基准延时程序
   {
    ;
   }
  }
 
}
void delay500us(void)
{
  int j;
  for(j=0;j<57;j++)
  {
   ;
  }
}

void beep(void)
{
  uchar t;
  for(t=0;t<100;t++)
  {
   delay500us();
 FMQ=!FMQ;   //产生脉冲
  }
  FMQ=1;    //关闭蜂鸣器
}

void motor_ccw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)                 //电机旋转一周，不是外面所看到的一周，是里面的传动轮转了一周
  {
   if(K3==0)
 {
   break;   //如果K3按下，退出此循环
 }
 for(i=0;i<8;i++)  //旋转45度
 {
   P1=CCW[i];
   delaynms(1);   //调节转速
 }
  }
}

void motor_cw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)
  {
   if(K3==0)
 {
   break;   //如果K3按下，退出此循环
 }
 for(i=0;i<8;i++)  //旋转45度
 {
   P1=CW[i];
   delaynms(2);   //调节转速
 }
  }
}


    