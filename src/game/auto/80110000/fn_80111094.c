#include "game/auto/m2c_prelude.h"
u32 fn_80111094(s8 *arg0) {
    u16 var_r4;
    u32 temp_r3;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0);
    var_r4 = 0;
    if (temp_r5 != NULL) {
        var_r4 = M2C_FIELD(temp_r5, u16 *, 0x10);
    }
    temp_r3 = (u32) (var_r4 * M2C_FIELD(arg0, u8 *, 4)) >> 1U;
    if (temp_r3 < 1U) {
        return 1U;
    }
    return temp_r3;
}
