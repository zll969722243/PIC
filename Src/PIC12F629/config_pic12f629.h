#ifndef __CONFIG_PIC12F629_HEADER_
#define __CONFIG_PIC12F629_HEADER_

#include <pic.h>

#define	byte	unsigned char
#define	word	unsigned int

typedef enum _em_fun_num
{
	TIMER0_FUN_NUM	=0,
	TIMER1_FUN_NUM	=1,
	CMP_FUN_NUM		=2,
	MEM_FUN_NUM		=3,
	EEPROM_FUN_NUM	=4,
	INST_FUN_NUM	=5,
	NULL_FUN_NUM,
	MAX_FUN_NUM
}em_fun_num;
	

//timer0 �������
#define TMR0_DELAY_S	1

//��������led1����GP0������,������ʱ���GP0,�����ֲ�����ܰ���ʱ,��ΪGP2
#define LED_OUT			GP0
#define LED_ON			0
#define LED_OFF			1

//PIC12F629�ıȽ���IO��ӳ���ϵ
#define CINHIG	GP0
#define CINLOW	GP1
#define CMPOUT	GP2

#define CMPINHIG_CNF TRISIO0
#define CMPINLOW_CNF TRISIO1
#define CMPOUT_CNF   TRISIO2

#endif