#ifndef __SHEDULE_HEADER_
#define __SHEDULE_HEADER_

#include "common.h"

byte init_shedule(void);
byte shedule(word funcnum);
byte need_shedule(word new_funcnum);


byte cur_timer0(word p);
byte new_timer0(word p);

byte cur_timer1(word p);
byte new_timer1(word p);

byte cur_cmp(word p);
byte new_cmp(word p);

byte cur_mem(word p);
byte new_mem(word p);

byte cur_eeprom(word p);
byte new_eeprom(word p);

byte cur_inst(word p);
byte new_inst(word p);

byte cur_def(word p);
byte new_def(word p);

#endif