#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_80306F9C(s32, s32, s32);
extern u32 lbl_803BFA98[0x10];
extern s8 lbl_804CB0EA;

void fn_80022158(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_r29;

    temp_r29 = arg1 + (arg2 << 0x10);
    if (temp_r29 != lbl_803BFA98[arg0]) {
        fn_80306F9C(arg0, arg1, arg2);
        lbl_803BFA98[arg0] = temp_r29;
        lbl_804CB0EA = 1;
    }
}

