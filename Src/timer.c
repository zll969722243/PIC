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
	T0IE = 0;	//禁止TMR0溢出中断
	T0IF = 0;   //清除T0中断标志
	
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
    led_out 	= 1;         
	
	//CLKOUT--->4M---4分频--->1M---256分频--->3906.25Hz
	//(0x100-x) * n = 3906.25
	//令x=156,则n=39;
	
	TMR0 		= 156;		 //每39次溢出是1S就
	GIE 		= 1;         //总中断使能
	T0IE 		= 1;		 //使能TMR0溢出中断
	T0IF		= 0;         //清除T0中断标志
	
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
		if(cnt==39*5)//39 * n,则为n秒的定时器
		{
			led_out = ~led_out;
			cnt = 0;
		}
	}
}
