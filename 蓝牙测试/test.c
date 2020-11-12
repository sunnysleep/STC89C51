#include <reg52.h>

sbit P1_0 = P1^0;	//测试口，可用可不用
sbit P1_3 = P1^3;	//输出口

unsigned char tempbuf;	//存储接收到的信息

/*初始化串口*/
void BlueteethInit()
{
	SCON = 0x50;	//串口模式1，允许接收
	TMOD = 0x20;	//T1工作模式为2，自动重装
	PCON = 0x00;	//波特率不倍增

	REN = 1;

	TH1 = 0xfd;		//设置波特率为9600
	TL1 = 0xfd;

	RI = 0;

	EA = 1;
	ES = 1;

	TR1 = 1;
}

void main()
{
	BlueteethInit();
	P1_0 = 0;
	P1_3 = 0;
	TI = 0;
	while(1)
	{
		if(tempbuf == 0x31)	//可以使用
			P1_3 = 1;
		if(tempbuf == 0)	//不可以使用
			P1_3 = 0;
		if(tempbuf == 'A')	//可以使用
			P1_3 = 1;
		if(tempbuf == 'B')	//可以使用
			P1_3 = 0;
	}
}

void Serial(void) interrupt 4
{
	tempbuf = SBUF;
	RI = 0;	//读标志清零
	SBUF = tempbuf;	//将内容返回到手机端，可在手机查看发送的内容
	while(!TI);
	TI = 0;	//写标志清零
}
