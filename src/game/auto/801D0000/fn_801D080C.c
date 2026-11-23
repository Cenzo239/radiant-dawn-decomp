#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_801D080C(u8 *arg0) {
    s32 var_r4;
    u8 temp_r0;
    s8 **var_r3;
    s8 *temp_r3;

    temp_r0 = *arg0;
    var_r4 = -1;
    if ((s8) temp_r0 >= 0) {
        var_r4 = (s8) temp_r0;
    }
    if (var_r4 < 0) {
        var_r3 = NULL;
    } else {
        var_r3 = arg0 + (var_r4 << 5) + 0x50;
    }
    if (var_r3 == NULL) {
        return 0;
    }
    temp_r3 = *var_r3;
    if (temp_r3 != NULL) {
        return M2C_FIELD(temp_r3, s32 *, 0x3F0);
    }
    return 0;
}

