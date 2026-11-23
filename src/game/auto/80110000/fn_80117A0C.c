#include "game/auto/m2c_prelude.h"
s32 fn_80117A0C(s8 *arg0, s8 arg1, s8 arg2) {
    s32 var_r0;

    if (arg1 < (s8) M2C_FIELD(arg0, u8 *, 8)) {
        var_r0 = 0;
    } else if (arg1 >= (s8) M2C_FIELD(arg0, u8 *, 0xA)) {
        var_r0 = 0;
    } else if (arg2 < (s8) M2C_FIELD(arg0, u8 *, 9)) {
        var_r0 = 0;
    } else {
        var_r0 = arg2 < (s8) M2C_FIELD(arg0, u8 *, 0xB);
    }
    return var_r0 == 0;
}
