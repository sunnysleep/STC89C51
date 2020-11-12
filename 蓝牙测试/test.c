#include <reg52.h>

sbit P1_0 = P1^0;	//���Կڣ����ÿɲ���
sbit P1_3 = P1^3;	//�����

unsigned char tempbuf;	//�洢���յ�����Ϣ

/*��ʼ������*/
void BlueteethInit()
{
	SCON = 0x50;	//����ģʽ1���������
	TMOD = 0x20;	//T1����ģʽΪ2���Զ���װ
	PCON = 0x00;	//�����ʲ�����

	REN = 1;

	TH1 = 0xfd;		//���ò�����Ϊ9600
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
		if(tempbuf == 0x31)	//����ʹ��
			P1_3 = 1;
		if(tempbuf == 0)	//������ʹ��
			P1_3 = 0;
		if(tempbuf == 'A')	//����ʹ��
			P1_3 = 1;
		if(tempbuf == 'B')	//����ʹ��
			P1_3 = 0;
	}
}

void Serial(void) interrupt 4
{
	tempbuf = SBUF;
	RI = 0;	//����־����
	SBUF = tempbuf;	//�����ݷ��ص��ֻ��ˣ������ֻ��鿴���͵�����
	while(!TI);
	TI = 0;	//д��־����
}
