#include<reg52.h> 
#include<intrins.h>

typedef unsigned int unint;
typedef unsigned char unchar;

unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

sbit LSA = P2^2; 
sbit LSB = P2^3;
sbit LSC = P2^4;
sbit TRIG = P1^4;
sbit ECHO = P1^5; 

unchar flag = 0; 

void delayed(unsigned int x);
void delay_20us(); 
void init_time();  
void display(int num); 
void DigDisplay(unint i);
void display2(unint num);
void display2(unint num)		//测试用显示（测试能否分段）
{
		DigDisplay(4);
		P0=table[num];//发送段码
		delayed(50); //间隔一段时间扫描	
		P0=0x00;//消隐
}
void main()
{
    int x; 
    unint time_data,out_TH0,out_TL0;

    TRIG = 0; 

    while(1)
    {

        init_time(); 
        flag = 0;  

        TRIG = 1;    
        delay_20us();
        TRIG = 0;

        while(!ECHO);
        TR0 = 1; 
        while(ECHO); 
        TR0 = 0; 

        out_TH0 = TH0;
        out_TL0 = TL0;
        out_TH0 <<= 8;  
        time_data = out_TH0 | out_TL0; 
        time_data /= 58; 
     
        for(x =5; x >=0; x--)
        {
			display(time_data);
//			if(time_data<10)
//            	{
//					display2(1);
//				}
//			else if(time_data<20&&time_data<30)
//				{
//					display2(2);
//				}
//			else if(time_data>=30)
//				{
//					
//					display2(4);
//				}
        }   
    }

}

void timer0() interrupt 1 
{
    flag=1;
}

void delayed(unsigned int x) 
{
    unsigned int i,j;
    for(i = x; i > 0; i--)
    {
        for(j = 113; j >0; j--);
    }
}

void init_time()
{
    TMOD = 0x01; 
    TH0 = 0;
    TL0 = 0;

    TF0 = 0; 
    ET0 = 1; 
    EA = 1; 
}

void DigDisplay(unint i)
{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(1):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(2):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(3):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
	
		}
	}
void display(int num)
{
    if(num == -1)
    {
		DigDisplay(0);
		P0=table[8];//发送段码
		delayed(100); //间隔一段时间扫描	
		P0=0x00;//消隐
    }
    else 
    {
        unchar t;
        t = num / 100;

		DigDisplay(3);
		P0=table[t];//发送段码
		delayed(10); //间隔一段时间扫描	
		P0=0x00;//消隐

        t = num/10%10; 
        DigDisplay(2);
		P0=table[t];//发送段码
		delayed(10); //间隔一段时间扫描	
		P0=0x00;//消隐

        t = num %10;
        DigDisplay(1);
		P0=table[t];//发送段码
		delayed(10); //间隔一段时间扫描	
		P0=0x00;//消隐
    }

}

void delay_20us()
{
    _nop_();_nop_();_nop_();_nop_();_nop_(); 
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
}
