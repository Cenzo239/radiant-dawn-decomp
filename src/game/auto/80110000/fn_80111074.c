#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_80111074(s8 *arg0) {
    s8 *temp_r4;
    u16 var_r5;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0);
    var_r5 = 0;
    if (temp_r4 != NULL) {
        var_r5 = M2C_FIELD(temp_r4, u16 *, 0x10);
    }
    return var_r5 * M2C_FIELD(arg0, u8 *, 4);
}

