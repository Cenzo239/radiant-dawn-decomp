#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800E272C(char *);
#else
s32 fn_800E272C();
#endif

s32 fn_800E2D14(s8 *arg0) {
    s32 var_r3;
    s8 *temp_r3;

    temp_r3 = M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s8 **, 0xC4);
    if (temp_r3 == NULL) {
        var_r3 = 0;
    } else {
        var_r3 = M2C_FIELD(temp_r3, s32 *, 4);
    }
    if (fn_800E272C(var_r3) == 0) {
        return 1;
    }
    return 0;
}
