#include "shedule.h"

__CONFIG(0x3194);

//��c����Ƕ�׻����ʵ�� ��ι����
#define  clrwdt()   asm("CLRWDT")

byte init(void);
word get_func_num(void);
