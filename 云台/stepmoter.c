#include<stepmoter.h>
#include<intrins.h>
 
 uchar code CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //��ʱ����ת�����
 uchar code CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //��ʱ����ת�����

void delaynms(uint aa)
{
  uchar bb;
  while(aa--)
  {
   for(bb=0;bb<115;bb++)     //1ms��׼��ʱ����
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
 FMQ=!FMQ;   //��������
  }
  FMQ=1;    //�رշ�����
}

void motor_ccw(void)
{
  uchar i,j;
  for(j=0;j<8;j++)                 //�����תһ�ܣ�����������������һ�ܣ�������Ĵ�����ת��һ��
  {
   if(K3==0)
 {
   break;   //���K3���£��˳���ѭ��
 }
 for(i=0;i<8;i++)  //��ת45��
 {
   P1=CCW[i];
   delaynms(1);   //����ת��
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
   break;   //���K3���£��˳���ѭ��
 }
 for(i=0;i<8;i++)  //��ת45��
 {
   P1=CW[i];
   delaynms(2);   //����ת��
 }
  }
}


    