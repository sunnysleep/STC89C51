#include<reg52.h> 
#include<intrins.h>

typedef unsigned int unint;
typedef unsigned char unchar;

unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

sbit we = P2^7;	//λ���������λѡ�������ӿ�
sbit du = P2^6;	//λ��������ܶ�ѡ�������ӿ�
sbit TRIG = P1^4;
sbit ECHO = P1^5; 

unchar flag = 0; 

void delayed(unsigned int x);
void delay_20us(); 
void init_time();  
void display(int num); 
//void display2(unint num);
//void display2(unint num)		//��������ʾ�������ܷ�ֶΣ�
//{
//		DigDisplay(4);
//		P0=table[num];//���Ͷ���
//		delayed(50); //���һ��ʱ��ɨ��	
//		P0=0x00;//����
//}
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
		

void display(int num)
{
    if(num == -1)
    {
			P0 = 0xfe;//1111 1110 ��һλ�������ʾ��ע������ܵ�����P0.0��Ӧ���ӵ�����ߵ�һλ�����
			we = 1;//��λѡ
			we = 0;	//�ر�λѡ

			P0=table[8];//���Ͷ���
			du = 1;	//�򿪶�ѡ
			du = 0;	//�رն�ѡ
			delayed(2);//��ʱ		
    }
    else 
    {
        unchar t;
        t = num / 100;

			P0 = 0xfe;//1111 1110 ��һλ�������ʾ��ע������ܵ�����P0.0��Ӧ���ӵ�����ߵ�һλ�����
			we = 1;//��λѡ
			we = 0;	//�ر�λѡ

			P0=table[t];
			du = 1;	//�򿪶�ѡ
			du = 0;	//�رն�ѡ
			delayed(2);//��ʱ


        t = num/10%10; 
			P0 = 0xfd;//1111 1101  ֻѡͨ�ڶ�λ�����
			we = 1;	//��λѡ
			we = 0;	//�ر�λѡ
			
			P0=table[t]; //��ʾ2
			du = 1;//�򿪶�ѡ
			du = 0;	//�رն�ѡ
			delayed(2);//��ʱ

        t = num %10;
			P0 = 0xfb;// 1111 1011ֻѡͨ����λ�����
			we = 1;	//��λѡ
			we = 0;	//�ر�λѡ
			
			P0=table[t]; //��ʾ3
			du = 1;//�򿪶�ѡ
			du = 0;	//�رն�ѡ
			delayed(2);//��ʱ
    }

}

void delay_20us()
{
    _nop_();_nop_();_nop_();_nop_();_nop_(); 
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
}
