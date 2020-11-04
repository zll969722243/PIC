#include "shedule.h"
#include "timer.h"
#include "eeprom.h"
#include "cmp.h"


#if 0

	typedef byte (*pfun)(word);
	typedef struct _func_num2proc
	{
		em_fun_num funcnum;
		pfun curproc;
		pfun newproc;
	}func_num2proc;

	static func_num2proc shedule_tbl[]=
	{
		TIMER0_FUN_NUM,cur_timer0,new_timer0,
		TIMER1_FUN_NUM,cur_timer1,new_timer1,
		CMP_FUN_NUM,cur_cmp,new_cmp,
		MEM_FUN_NUM,cur_mem,new_mem,
		EEPROM_FUN_NUM,cur_eeprom,new_eeprom,
		INST_FUN_NUM,cur_inst,new_inst,
		NULL_FUN_NUM,cur_def,new_def
	};
	
#endif

byte init_shedule(void)
{
	return 1;
}


byte need_shedule(byte new_funcnum)
{
	static byte cur_funcnum = NULL_FUN_NUM;
	if(cur_funcnum != new_funcnum)
	{
		cur_funcnum = new_funcnum;
		return 1;
	} 
	else return 0;		
}

#if 0
//PIC12F629内存太小了,不支持定义一个全局数组.无奈.
byte shedule(byte new_funcnum)
{
	static byte cur_funcnum_index = 0;
	byte index = 0;
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
			g_func_num_4_dbg = new_funcnum+1;
			break;
		}
	}
	
	return 1;
}
#endif

byte shedule(byte new_funcnum)
{
	static byte cur_funcnum = NULL_FUN_NUM;

//	if(new_funcnum==7) new_funcnum=0;
//	else if (new_funcnum==3) new_funcnum=1;

	if(new_funcnum>=MAX_FUN_NUM)
		return 0;
	
	if(!exec_proc(cur_funcnum,0,0))//当前的测试模块自己把屁股擦干净
		return 0;
	if(!exec_proc(new_funcnum,1,0))//开启新的模块测试
		return 0;
		
	cur_funcnum = new_funcnum;//update

	return 1;
}

byte exec_proc(byte funcnum,byte isnew,byte p)
{
	switch(funcnum)
	{
		case TIMER0_FUN_NUM:
		{
			return (isnew ? new_timer0(p): cur_timer0(p));
		}
		case TIMER1_FUN_NUM:
		{
			return (isnew ? new_timer1(p): cur_timer1(p));
		}
		case CMP_FUN_NUM:
		{
			return (isnew ? new_cmp(p): cur_cmp(p));
		}
		case MEM_FUN_NUM:
		{
			//return (isnew ? new_mem(p): cur_mem(p));
			return (isnew ? new_timer0(p): cur_timer0(p));
		}
		case EEPROM_FUN_NUM:
		{
			return (isnew ? new_eeprom(p): cur_eeprom(p));
		}
		case INST_FUN_NUM:
		{
			//return (isnew ? new_inst(p): cur_inst(p));
			return (isnew ? new_timer1(p): cur_timer1(p));
		}
		case NULL_FUN_NUM:	
		{
			return (isnew ? new_def(p): cur_def(p));
		}
		default:
			return 0;
	}
}

byte cur_timer0(byte p)
{
	return uninit_timer0();
}

byte new_timer0(byte p)
{
	return init_timer0();
}


byte cur_timer1(byte p)
{
	return uninit_timer1();
}

byte new_timer1(byte p)
{
	return init_timer1();
}


byte cur_cmp(byte p)
{
	return uninit_timer0();
}

byte new_cmp(byte p)
{
	return init_cmp();
}


byte cur_mem(byte p)
{
	return uninit_cmp();
}

byte new_mem(byte p)
{
	return 1;
}


byte cur_eeprom(byte p)
{
	if(!uninit_eeprom())
		return 0;
		
	return 1;	
}

byte new_eeprom(byte p)
{
	if(!init_eeprom())
		return 0;
		
	return test_write_read(0);
}


byte cur_inst(byte p)
{
	return 1;
}

byte new_inst(byte p)
{
	return 1;
}


byte cur_def(byte p)
{
	return 1;
}

byte new_def(byte p)
{
	return 1;
}



