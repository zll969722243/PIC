#include "timer.h"

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
	GIE  = 0;   //���жϽ�ֹ
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
    LED_OUT		= LED_OFF;         
	
	//CLKOUT--->4M---4��Ƶ--->1M---256��Ƶ--->3906.25Hz
	//(0x100-x) * n = 3906.25
	//��x=156,��n=39;
	
	TMR0 		= 156;		 //ÿ39�������1S��
	GIE 		= 1;         //���ж�ʹ��
	T0IE 		= 1;		 //ʹ��TMR0����ж�
	T0IF		= 0;         //���T0�жϱ�־
	
	return 1;	
}

byte uninit_timer1()
{
	TMR1ON=0;       //ֹͣ����T1��ʱ
	TMR1IF=0;       //���T1�жϱ�־	
	TMR1IE=0;       //T1�жϽ�ֹ
	PEIE  =0;       //ʹ�ܽ�ֹ��Χ����
	GIE   =0;       //���ж�ʹ��
	
	return 1;
}

byte init_timer1(void)
{
	OPTION_REG 	= 0X07;             
    LED_OUT 	= LED_OFF;         
	
	GIE=1;                  //���ж�ʹ��
	T1CON=0X34;             //8��Ƶ,Fosc/4
	TMR1IF=0;               //���T1�жϱ�־
	
	//4M/4 = 1M = 10^6
	//10^6 / 8 = 125000
	//65536 - 12500 = 53036
	TMR1L=44;             //��ʱ����ʼֵ
	TMR1H=207;
	
	PEIE=1;                 //ʹ����Χ����
	TMR1IE=1;               //T1�ж�ʹ��
	TMR1ON=1;               //����T1��ʱ
 	
	return 1;	
}

//void interrupt tmer0(void)
//{
//	static byte cnt = 0;
//	if(T0IF==1)
//	{
//		cnt++;
//		TMR0=156;
//		T0IF=0;	
//		if(cnt==39*TMR0_DELAY_S)//39 * n,��Ϊn��Ķ�ʱ��,TMR0_DELAY_S��common.h������
//		{
//			led_out = ~led_out;
//			cnt = 0;
//		}
//	}
//}

extern byte g_func_num_4_dbg;

void interrupt tmer0(void)
{
	static byte cnt_tmer0 = 0;
	static byte cnt_tmer1 = 0;
	if((T0IF==1) && (T0IE==1))
	{
		cnt_tmer0++;
		TMR0=156;
		T0IF=0;
		
		if(cnt_tmer0==39*1)//39 * n,��Ϊn��Ķ�ʱ��
		{
			LED_OUT = ~LED_OUT;
			cnt_tmer0 = 0;
		}
	}
	else if((TMR1IF==1) && (TMR1IE==1))
	{
		cnt_tmer1++;
		TMR1L=44;
		TMR1H=207;
		TMR1IF=0;
		
		if(cnt_tmer1==10*2)//39 * n,��Ϊn��Ķ�ʱ��
		{
			//LED_OUT = ~LED_OUT;
			GP1 = ~GP1;
			cnt_tmer1 = 0;
		}
	}
}