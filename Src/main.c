#include "main.h"
#include "./Utils/utils.h"

__CONFIG(0x3194);

void main(void)
{
	init();
	
	while(1)
	{
		
		byte funcnum = get_func_num();
		
		if(need_shedule(funcnum)) 
			shedule(funcnum);
		
		clrwdt();
		delay(50);
//		GP0=0;
//		delay(50);	
//		GP0=1;	
//		delay(50);	
	}
}

byte init(void)
{	//refer to config.txt
	TRISIO0  	= 0;         //set GPO0 to output
	TRISIO1  	= 0;		 //set GPO1 to output
	TRISIO2  	= 0;		 //set GPO2 to output
	
	TRISIO3  	= 1;         //set GPO3 to input
	TRISIO4  	= 1;         //set GPO4 to input
	TRISIO5  	= 1;         //set GPO5 to input
	
	//CMCON=0X07;				 //disable cmp
	return init_shedule();
}

byte get_func_num(void)
{	
	byte tmp3=GP5;
	byte tmp2=GP4;
	byte tmp1=GP3;
	
	byte funcnum = (tmp3<<2)+(tmp2<<1)+tmp1;

	
		//if(funcnum==6)
		if(GP5==1 && GP4==1&& GP3==1)
		{
			GP1=1;
		}
		else if(GP5==1 && GP4==1&& GP3==0)
		{
			GP1=0;
		}
	
	
	return funcnum; 
}



////引用头文件
//#include<pic.h>
//#define  clrwdt()   asm("CLRWDT")
//__CONFIG(0x31B4);	//参考：《PIC12F629/675数据手册》第52页 9.1 配置位
//
//#define     led1		GP0
//#define     led2        GP1 
//
//void delay1(int z)
//{
//	int x,y;
//	
//	for(x=0;x<200;x++)
//		for(y=0;y<z;y++);
//}
//
//
//
//void main(void)
//{
//	TRISIO0  	= 0;         //set GPO0 to output
//	TRISIO1  	= 0;		 //set GPO1 to output
//	TRISIO2  	= 0;		 //set GPO2 to output
//	
//	TRISIO3  	= 1;         //set GPO3 to input
//	TRISIO4  	= 1;         //set GPO4 to input
//	TRISIO5  	= 1;         //set GPO5 to input
//
//
//	while(1)
//	{
//		
//		led1=1;
//		clrwdt();
//		delay(100);	
//		led1=0;	
//		delay(100);	
//	}
//}
