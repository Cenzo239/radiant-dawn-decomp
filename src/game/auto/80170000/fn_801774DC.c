#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80081194(void *, void *);
#else
s8 * fn_80081194();
#endif
extern u8 lbl_80387A78[0x20];

void fn_801774DC(s32 arg0, s16 arg1) {
    M2C_FIELD(fn_80081194(lbl_80387A78, arg0), s16 *, 0x32) = arg1;
}
