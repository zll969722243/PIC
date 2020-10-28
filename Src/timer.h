#ifndef __TIMER_HEADER_
#define __TIMER_HEADER_

#include "common.h"

//ret:
//1:success;
//0:fail;
byte init_timer0(void);

byte start_timer0();

byte stop_timer0();

byte uninit_timer0();


#endif 
