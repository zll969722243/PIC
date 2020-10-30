#include "main.h"
#include "utils.h"

__CONFIG(0x3194);

void main(void)
{
	TRISIO1=0;
	//init();
	while(1)
	{
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
	
	CMCON=0X07;				 //disable cmp
	
	return init_shedule();
}

byte get_func_num(void)
{	
	byte tmp3=GP5;
	byte tmp2=GP4;
	byte tmp1=GP3;
	
	byte funcnum = (tmp3<<2)+(tmp2<<1)+tmp1;
	
	//(GP5==0) && (GP4==1) && (GP3==0)
	//if((GP5==1) && (GP4==1) && (GP3==0))
	
	#if 0
	
		//if(funcnum==6)
		if((GP5==0) && (GP4==1) && (GP3==1))
		{
			GP1=0;
		}
		else
		{
			GP1=1;
		}
	
	#endif
	
	return funcnum; 
}