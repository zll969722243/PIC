#ifndef __EEPROM_HEADER_
#define __EEPROM_HEADER_

#include "common.h"

//ret:
//1:success;
//0:fail;
byte init_eeprom(void);

byte start_eeprom();

byte stop_eeprom();

byte uninit_eeprom();


#endif 