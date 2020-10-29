#include "shedule.h"
#include "timer.h"


typedef byte (*pfun)(word);
typedef struct _func_num2proc
{
	em_fun_num funcnum;
	pfun curproc;
	pfun newproc;
}func_num2proc;

//static funcnum2proc shedule_tbl[]=
//{
//	TIMER0_FUN_NUM,cur_timer0,new_timer0,
//	TIMER1_FUN_NUM,cur_timer1,new_timer0,
//	CMP_FUN_NUM,cur_cmp,new_timer0,
//	MEM_FUN_NUM,cur_mem,new_timer0,
//	EEPROM_FUN_NUM,cur_eeprom,new_timer0,
//	INST_FUN_NUM,cur_inst,new_timer0,
//	NULL_FUN_NUM,cur_def,new_timer0
//};

static func_num2proc shedule_tbl[]=
{
	TIMER0_FUN_NUM,cur_timer0,new_timer0,
	TIMER1_FUN_NUM,cur_timer0,new_timer0,
	CMP_FUN_NUM,cur_timer0,new_timer0,
	MEM_FUN_NUM,cur_timer0,new_timer0,
	EEPROM_FUN_NUM,cur_timer0,new_timer0,
	INST_FUN_NUM,cur_timer0,new_timer0,
	NULL_FUN_NUM,cur_timer0,new_timer0
};

byte init_shedule(void)
{
	return 1;
}


byte need_shedule(word new_funcnum)
{
	static word cur_funcnum = NULL_FUN_NUM;
	if(cur_funcnum != new_funcnum)
	{
		cur_funcnum = new_funcnum;
		return 1;
	} 
	else return 0;		
}


byte shedule(word new_funcnum)
{
	static word cur_funcnum_index = 0;
	word index = 0;
	//new_funcnum=0;
	
	if(new_funcnum>=MAX_FUN_NUM)
		return 0;
	
	for(;index<(sizeof(shedule_tbl)/sizeof(func_num2proc));index++)
	{
		if(new_funcnum == (word)shedule_tbl[index].funcnum)
		{
			if(!(shedule_tbl[cur_funcnum_index].curproc(0))) 
				return 0;//当前的测试模块自己把屁股擦干净
				
			if(!shedule_tbl[index].newproc(0)) 
				return 0;//开启新的模块测试
			
			cur_funcnum_index = index;//update
			
			break;
		}
	}
	
	return 1;
}


byte cur_timer0(word p)
{
	return uninit_timer0();
}

byte new_timer0(word p)
{
	return init_timer0();
}


byte cur_timer1(word p)
{
	return 1;
}

byte new_timer1(word p)
{
	return 1;
}


byte cur_cmp(word p)
{
	return 1;
}

byte new_cmp(word p)
{
	return 1;
}


byte cur_mem(word p)
{
	return 1;
}

byte new_mem(word p)
{
	return 1;
}


byte cur_eeprom(word p)
{
	return 1;
}

byte new_eeprom(word p)
{
	return 1;
}


byte cur_inst(word p)
{
	return 1;
}

byte new_inst(word p)
{
	return 1;
}


byte cur_def(word p)
{
	return 1;
}

byte new_def(word p)
{
	return 1;
}



