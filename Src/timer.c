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
	T0IE = 0;	//禁止TMR0溢出中断
	T0IF = 0;   //清除T0中断标志
	GIE  = 0;   //总中断禁止
	return 1;
}

/* 	INTCON—中断控制寄存器 地址Addr:0Bh 或 8Bh; 默认值为0000 0000
	bit7							  bit0	
	GIE PEIE T0IE INTE GPIE T0IF INTF GPI
	
	GIE:全局中断使能位,1=使能所有未屏蔽的中断
	T0IE:TMR0溢出中断使能位,1=使能TMR0溢出中断
	T0IF:TMR0溢出中断标志位,1=TMR0寄存器已经溢出,必须用软件清零
	
	当TIMER0计满回零时,T0IF被置位.复位时TIMER0的状态不变,应在清零T0IF位前初始化. 
*/

//选择内部时钟CLKOUT
//TIMER预分频为1:256
byte init_timer0(void)
{
	OPTION_REG 	= 0X07;             
    LED_OUT		= LED_OFF;         
	
	//CLKOUT--->4M---4分频--->1M---256分频--->3906.25Hz
	//(0x100-x) * n = 3906.25
	//令x=156,则n=39;
	
	TMR0 		= 156;		 //每39次溢出是1S就
	GIE 		= 1;         //总中断使能
	T0IE 		= 1;		 //使能TMR0溢出中断
	T0IF		= 0;         //清除T0中断标志
	
	return 1;	
}

byte uninit_timer1()
{
	TMR1ON=0;       //停止启动T1计时
	TMR1IF=0;       //清除T1中断标志	
	TMR1IE=0;       //T1中断禁止
	PEIE  =0;       //使能禁止外围功能
	GIE   =0;       //总中断使能
	
	return 1;
}

byte init_timer1(void)
{
	OPTION_REG 	= 0X07;             
    LED_OUT 	= LED_OFF;         
	
	GIE=1;                  //总中断使能
	T1CON=0X34;             //8分频,Fosc/4
	TMR1IF=0;               //清除T1中断标志
	
	//4M/4 = 1M = 10^6
	//10^6 / 8 = 125000
	//65536 - 12500 = 53036
	TMR1L=44;             //定时器初始值
	TMR1H=207;
	
	PEIE=1;                 //使能外围功能
	TMR1IE=1;               //T1中断使能
	TMR1ON=1;               //启动T1计时
 	
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
//		if(cnt==39*TMR0_DELAY_S)//39 * n,则为n秒的定时器,TMR0_DELAY_S在common.h中配置
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
		
		if(cnt_tmer0==39*1)//39 * n,则为n秒的定时器
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
		
		if(cnt_tmer1==10*2)//39 * n,则为n秒的定时器
		{
			//LED_OUT = ~LED_OUT;
			GP1 = ~GP1;
			cnt_tmer1 = 0;
		}
	}
}