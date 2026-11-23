#include "game/auto/m2c_prelude.h"
s8 *fn_801D07D8(u8 *arg0) {
    s32 var_r4;
    u8 temp_r0;

    temp_r0 = *arg0;
    var_r4 = -1;
    if ((s8) temp_r0 >= 0) {
        var_r4 = 1 - (s8) temp_r0;
    }
    if (var_r4 < 0) {
        return NULL;
    }
    return arg0 + (var_r4 << 5) + 0x50;
}
