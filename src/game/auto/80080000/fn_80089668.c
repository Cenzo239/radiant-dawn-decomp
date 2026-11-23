#include "game/auto/m2c_prelude.h"
s32 fn_8007857C();
#if TARGET_PC
FE10_PROTO int fn_800785FC(char *, unsigned int);
#else
M2C_UNK fn_800785FC();
#endif

s32 fn_80089668(s8 *arg0) {
    s32 temp_r31;
    s32 var_r4;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 4);
    var_r4 = M2C_FIELD(temp_r5, s32 *, 8);
    temp_r31 = M2C_FIELD(temp_r5, s32 *, 4);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r5 + 0xC);
    if (var_r4 < 0) {
        var_r4 = fn_8007857C();
    }
    fn_800785FC(temp_r31, var_r4);
    return 1;
}
