#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int * fn_80078CCC(int, ...);
FE10_PROTO int fn_801148D8(void *, unsigned int);
#else
s32 fn_80078CCC();
s32 fn_801148D8();
#endif
M2C_UNK fn_80170F50();
M2C_UNK memset();
extern u8 lbl_8036B0D0[0xf];
extern u8 lbl_803EC898[0x15867];
extern u8 lbl_804183F0[0x250];
extern s32 lbl_804CB8C4;

void fn_80165820(void) {
    M2C_FIELD(lbl_804183F0, s32 *, 8) = 0xFFFF;
    M2C_FIELD(lbl_804183F0, s8 *, 0xC) = 2;
    fn_80170F50(0xFFFF);
    memset(lbl_804183F0 + 0x10, 0, 0x14);
    lbl_804CB8C4 = fn_80078CCC(fn_801148D8(lbl_803EC898, 6), lbl_8036B0D0 + 0xF, 0);
}

