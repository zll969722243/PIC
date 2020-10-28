#include "shedule.h"

__CONFIG(0x3194);

//用c语言嵌套汇编来实现 “喂狗”
#define  clrwdt()   asm("CLRWDT")

byte init(void);
word get_func_num(void);
