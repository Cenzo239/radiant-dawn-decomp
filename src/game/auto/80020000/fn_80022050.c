#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_80306F4C(s32, u32);
extern u32 lbl_803BFA58[0x10];
extern s8 lbl_804CB0E9;

void fn_80022050(s32 arg0, u32 arg1) {
    s32 temp_r30;

    temp_r30 = arg0 * 4;
    if (arg1 != lbl_803BFA58[arg0]) {
        fn_80306F4C(arg0, arg1);
        lbl_803BFA58[arg0] = arg1;
        lbl_804CB0E9 = 1;
    }
}

