#include "game/auto/m2c_prelude.h"
extern s8 *lbl_804CB628;

void fn_800A28D8(s8 *arg0) {
    s8 *temp_r4;
    s8 *var_r5;

    if ((s32) M2C_FIELD(arg0, u8 *, 0x2D) != 0) {
        goto block_8;
    }
    var_r5 = arg0;
    goto loop_5;
block_2:
    if ((u32) temp_r4 < 0x400U) {
        goto block_6;
    }
    if (!(M2C_FIELD(var_r5, u8 *, 0x2C) & 4)) {
        goto block_8;
    }
    var_r5 = temp_r4;
loop_5:
    temp_r4 = M2C_FIELD(var_r5, s8 **, 0x18);
    if (temp_r4 != NULL) {
        goto block_2;
    }
block_6:
    lbl_804CB628 = arg0;
    return;
block_8:
    return;
}
