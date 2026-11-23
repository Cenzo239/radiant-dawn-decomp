#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s32 fn_80083B84();
#endif
extern u8 lbl_80387810[0x50];

s32 fn_80174FD4(void) {
    return fn_80083B84(lbl_80387810) != 0;
}
