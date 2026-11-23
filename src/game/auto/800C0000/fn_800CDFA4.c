#include "game/auto/m2c_prelude.h"
u32 OSGetResetCode();
extern u8 lbl_803832E0[0x680];
extern s32 lbl_804CB700;

void fn_800CDFA4(void) {
    lbl_804CB700 = 0;
    if (((OSGetResetCode() >> 0x1FU) != 0) && !(OSGetResetCode() & 0x10000)) {
        lbl_804CB700 |= 0x10000000;
    }
    M2C_FIELD(lbl_803832E0, s32 *, 0x43C) = 0x1E100A;
    M2C_FIELD(lbl_803832E0, s32 *, 0x490) = 0x1E100A;
}
