#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800BD280(void *);
#else
s32 fn_800BD280();
#endif

s32 fn_800AE500(s8 *arg0) {
    s32 var_r31;
    s32 var_r3;
    s8 *temp_r4;
    s8 *var_r30;

    var_r31 = 0;
    var_r30 = arg0;
loop_1:
    if (var_r31 < 0) {
        var_r3 = 0;
    } else {
        var_r3 = M2C_FIELD(var_r30, s32 *, 0x3C);
    }
    if (fn_800BD280(var_r3) != 0) {
        temp_r4 = M2C_FIELD(var_r30, s8 **, 0x5C);
        if ((temp_r4 != NULL) && ((u32) M2C_FIELD(temp_r4, u32 *, 0x54) != (u32) M2C_FIELD(temp_r4, u32 *, 0x58))) {
            return 1;
        }
    }
    var_r31 += 1;
    var_r30 += 4;
    if (var_r31 >= 2) {
        return 0;
    }
    goto loop_1;
}
