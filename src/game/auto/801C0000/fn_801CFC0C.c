#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_801CFC0C(s8 *arg0) {
    s32 var_r4;
    s8 t;
    s8 *var_r3;
    t = *arg0;
    var_r4 = -1;
    if (t >= 0) {
        var_r4 = t;
    }
    if (var_r4 < 0) {
        var_r3 = NULL;
    } else {
        var_r3 = arg0 + (var_r4 << 5) + 0x50;
    }
    if (*(s16*)(var_r3 + 0xE) > 0) {
        return 1;
    }
    return 0;
}
