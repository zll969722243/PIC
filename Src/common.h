#ifndef __COMMON_HEADER_
#define __COMMON_HEADER_

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
	

//timer0 œ‡πÿ≈‰÷√
#define TMR0_DELAY_S	1

#endif