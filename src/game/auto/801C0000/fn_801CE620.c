#include "game/auto/m2c_prelude.h"
u8 fn_801CE620(s8 **arg0) {
    s8 *var_r3;
    s8 *temp_r4;
    s8 *var_r5;

    temp_r4 = *arg0;
    var_r5 = NULL;
    if (temp_r4 != NULL) {
        var_r3 = M2C_FIELD(temp_r4, s8 **, 0x3F0);
    } else {
        var_r3 = NULL;
    }
    if (var_r3 != NULL) {
        var_r5 = M2C_FIELD(var_r3, s8 **, 0xF4);
    } else if (temp_r4 != NULL) {
        var_r5 = M2C_FIELD(temp_r4, s8 **, 0xF4);
    }
    if (var_r5 == NULL) {
        return 0U;
    }
    return M2C_FIELD(var_r5, u8 *, 8);
}
