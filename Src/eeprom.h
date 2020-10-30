#ifndef __EEPROM_HEADER_
#define __EEPROM_HEADER_

#include "common.h"

//ret:
//1:success;
//0:fail;
byte init_eeprom(void);

byte read_eeprom(byte addr,byte *out);

byte write_eeprom(byte addr,byte data);

byte test_write_read(byte p);

byte uninit_eeprom(void);


#endif 