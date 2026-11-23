#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800607A0(void *);
#else
s32 fn_800607A0();
#endif
extern u8 lbl_803CAB38[0x988];

s32 fn_801D4300(void) {
    s32 temp_r3;

    temp_r3 = fn_800607A0(lbl_803CAB38);
    return ((s32) (-temp_r3 | temp_r3) >> 0x1F) & 2;
}
