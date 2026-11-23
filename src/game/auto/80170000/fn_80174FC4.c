#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081050(void *, void *);
#else
M2C_UNK fn_80081050();
#endif
extern u8 lbl_80387810[0x50];

void fn_80174FC4(void) {
    fn_80081050(lbl_80387810, 9);
}
