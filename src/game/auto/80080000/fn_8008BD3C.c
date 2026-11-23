#include "game/auto/m2c_prelude.h"
s8 *fn_8008BD3C(s8 *arg0, u16 *arg1, s8 **arg2, s8 *arg3, s8 *arg4) {
    s8 *var_r10;
    s8 *var_r11;

    *arg2 = NULL;
    var_r10 = arg0 + 4;
    var_r11 = M2C_FIELD(arg0, s8 **, 4);
    *arg3 = 1;
    *arg4 = 1;
    goto loop_4;
block_1:
    var_r10 = var_r11;
    if ((u16) *arg1 >= (u16) M2C_FIELD(var_r11, u16 *, 0xC)) {
        goto block_3;
    }
    var_r11 = M2C_FIELD(var_r11, s8 **, 0);
    *arg3 = 1;
    goto loop_4;
block_3:
    *arg2 = var_r11;
    var_r11 = M2C_FIELD(var_r11, s8 **, 4);
    *arg3 = 0;
    *arg4 = 0;
loop_4:
    if (var_r11 != NULL) {
        goto block_1;
    }
    return var_r10;
}
