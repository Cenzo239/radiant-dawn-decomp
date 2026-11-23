#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern f32 lbl_804CF6F4;

void fn_801CA9C4(s8 *arg0) {
    s8 *p;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0x30);
    p = M2C_FIELD(temp_r5, s8 **, 0x10);
    M2C_FIELD(temp_r5, u8 *, 0) = (u8) (M2C_FIELD(temp_r5, u8 *, 0) & 0xFFFFFFEF);
    if (M2C_FIELD(p, s32 *, 0xB8) & 0x01000000) {
        M2C_FIELD(temp_r5, u8 *, 0) = (u8) (M2C_FIELD(temp_r5, u8 *, 0) | 4);
        M2C_FIELD(temp_r5, s32 *, 0x14) = (s32) (M2C_FIELD(temp_r5, s32 *, 0x14) & 0xFFFFFFDF);
    } else {
        M2C_FIELD(temp_r5, s32 *, 0x14) = (s32) (M2C_FIELD(temp_r5, s32 *, 0x14) & 0xFFFFFFEF);
    }
    if ((s32) M2C_FIELD(arg0, u8 *, 0x48) == 0) {
        M2C_FIELD(temp_r5, f32 *, 0x8C) = (f32) lbl_804CF6F4;
    }
}

