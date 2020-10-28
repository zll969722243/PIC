#ifndef __INST_HEADER_
#define __INST_HEADER_

#include "common.h"

//ret:
//1:success;
//0:fail;
byte init_inst(void);

byte start_inst();

byte stop_inst();

byte uninit_inst();


#endif 