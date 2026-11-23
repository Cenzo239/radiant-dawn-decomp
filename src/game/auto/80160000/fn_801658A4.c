#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80078E24(void *, ...);
#else
M2C_UNK fn_80078E24();
#endif
extern u8 lbl_804183F0[0x250];
extern s32 lbl_804CB8C4;

void fn_801658A4(void) {
    M2C_FIELD(lbl_804183F0, s8 *, 2) = 0;
    fn_80078E24(lbl_804CB8C4, lbl_804183F0);
    lbl_804CB8C4 = 0;
}
