#include "timer.h"

#define led_out		GP0

byte test_start()
{
	return 0;
}

byte test_stop()
{
	return 0;
}

byte uninit_timer0()
{
	T0IE = 0;	//��ֹTMR0����ж�
	T0IF = 0;   //���T0�жϱ�־
	
	return 1;
}

/* 	INTCON���жϿ��ƼĴ��� ��ַAddr:0Bh �� 8Bh; Ĭ��ֵΪ0000 0000
	bit7							  bit0	
	GIE PEIE T0IE INTE GPIE T0IF INTF GPI
	
	GIE:ȫ���ж�ʹ��λ,1=ʹ������δ���ε��ж�
	T0IE:TMR0����ж�ʹ��λ,1=ʹ��TMR0����ж�
	T0IF:TMR0����жϱ�־λ,1=TMR0�Ĵ����Ѿ����,�������������
	
	��TIMER0��������ʱ,T0IF����λ.��λʱTIMER0��״̬����,Ӧ������T0IFλǰ��ʼ��. 
*/

//ѡ���ڲ�ʱ��CLKOUT
//TIMERԤ��ƵΪ1:256
byte init_timer0(void)
{
	OPTION_REG 	= 0X07;             
    led_out 	= 1;         
	
	//CLKOUT--->4M---4��Ƶ--->1M---256��Ƶ--->3906.25Hz
	//(0x100-x) * n = 3906.25
	//��x=156,��n=39;
	
	TMR0 		= 156;		 //ÿ39�������1S��
	GIE 		= 1;         //���ж�ʹ��
	T0IE 		= 1;		 //ʹ��TMR0����ж�
	T0IF		= 0;         //���T0�жϱ�־
	
	return 1;	
}

void interrupt tmer0(void)
{
	static byte cnt = 0;
	if(T0IF==1)
	{
		cnt++;
		TMR0=156;
		T0IF=0;	
		if(cnt==39*5)//39 * n,��Ϊn��Ķ�ʱ��
		{
			led_out = ~led_out;
			cnt = 0;
		}
	}
}
