#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char, ...);
#else
M2C_UNK fn_800453B4();
#endif
extern u8 lbl_803CA870[0x130];

s32 fn_8002486C(s32 arg0, s8 *arg1) {
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg1, s8 **, 0x18);
    M2C_FIELD(temp_r5, s8 *, 0x54) = 1;
    fn_800453B4(lbl_803CA870, 0x87, temp_r5);
    return 5;
}

