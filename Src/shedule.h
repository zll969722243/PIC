#ifndef __SHEDULE_HEADER_
#define __SHEDULE_HEADER_

#include "common.h"

byte init_shedule(void);
byte shedule(byte funcnum);
byte need_shedule(byte new_funcnum);
byte exec_proc(byte funcnum,byte isnew,byte p);

byte cur_timer0(byte p);
byte new_timer0(byte p);

byte cur_timer1(byte p);
byte new_timer1(byte p);

byte cur_cmp(byte p);
byte new_cmp(byte p);

byte cur_mem(byte p);
byte new_mem(byte p);

byte cur_eeprom(byte p);
byte new_eeprom(byte p);

byte cur_inst(byte p);
byte new_inst(byte p);

byte cur_def(byte p);
byte new_def(byte p);

#endif