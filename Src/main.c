#include "main.h"
#include "utils.h"

__CONFIG(0x31B4);

void main(void)
{
	init();
	while(1)
	{
		clrwdt();
		byte funcnum = get_func_num();
		
		if(need_shedule(funcnum)) 
			shedule(funcnum);
			
		clrwdt();
		delay(100);		
	}
}

byte init(void)
{	//refer to config.txt
	TRISIO0  	= 0;         //set GPO0 to output
	TRISIO3  	= 1;         //set GPO3 to input
	TRISIO4  	= 1;         //set GPO4 to input
	TRISIO5  	= 1;         //set GPO5 to input
	
	return init_shedule();
}

word get_func_num(void)
{	
	byte funcnum = GP5<<2+GP4<<1+GP3;
	return funcnum; 
}