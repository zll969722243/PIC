#include "eeprom.h"

byte init_eeprom(void)
{
	return 1;
}

byte read_eeprom(byte addr,byte *out)
{
	if(addr > 128 || !out)
		return 0;
		
	EEADR = addr;
	while(RD==1){}
	
	*out = EEDATA;
	return 1;
}

byte write_eeprom(byte addr,byte data)
{
	EEADR=addr;
	EEDATA=data;
	
	WREN=1;//Enable write
	GIE=0;//Disable INTS
	EECON2=0X55;
	EECON2=0XAA;
	
	WR=1;//Start the write
	GIE=1;//Enable INTS
	
	while(EEIF==0){}
	
	EEIF=0;
	WREN=0;
	
	return 1;
}

byte test_write_read(byte p)
{
	byte addr = 0;
	byte wdata = 0,rdata = 0;
	
	LED_OUT = LED_OFF;
	
	while(addr<128)
	{
		wdata = addr;
		if(!write_eeprom(addr,wdata))
			return 0;
		
		if(!read_eeprom(addr,&rdata))
			return 0;
			
		if(rdata!=wdata)
			return 0;
			
		addr++;
	}
	
	LED_OUT = LED_ON;
	return 1;
}

byte uninit_eeprom(void)
{
	return 1;
}











	
	
	
	
	