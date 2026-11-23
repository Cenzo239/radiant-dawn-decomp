#include "game/auto/m2c_prelude.h"
s32 fn_802401F4(s8 *arg0) {
    s32 temp_r4;
    s32 var_r5;

    temp_r4 = M2C_FIELD(arg0, s32 *, 8);
    var_r5 = 0;
    if (temp_r4 != 0) {
        var_r5 = 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        var_r5 += 1;
    }
    if (temp_r4 != 0) {
        var_r5 += 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x14) != 0) {
        var_r5 += 1;
    }
    if (temp_r4 != 0) {
        var_r5 += 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        var_r5 += 1;
    }
    return var_r5;
}
