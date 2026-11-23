#include "game/auto/m2c_prelude.h"
u8 fn_80110E58(s8 *arg0) {
    s32 var_r0;
    s8 var_r0_2;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_r4 == NULL) {
        return 0U;
    }
    if (((u8) M2C_FIELD(arg0, u8 *, 5) >> 5U) & 1) {
        var_r0_2 = (s8) M2C_FIELD(arg0, u8 *, 0x20);
    } else {
        var_r0_2 = 0;
    }
    var_r0 = M2C_FIELD(temp_r4, u8 *, 0x1F) + var_r0_2;
    if (var_r0 > 0xFF) {
        var_r0 = 0xFF;
    }
    if (var_r0 < 0) {
        var_r0 = 0;
    }
    return (u8) var_r0;
}
