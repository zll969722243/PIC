#include "cmp.h"

byte init_cmp(void)
{
	//refer to config.h
	CMPINHIG_CNF = 1;
	CMPINLOW_CNF = 1;
	CMPOUT_CNF = 0;
	
	CMCON = 0x41;
	
	return 1;
}

byte start_cmp()
{
	return 1;
}

byte stop_cmp()
{
	return 1;
}

byte uninit_cmp()
{
	CMCON = 0x07;
	
	return 1;
}
