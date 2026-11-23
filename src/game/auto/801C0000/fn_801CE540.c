#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_801092C4(unsigned short *);
#else
s32 fn_801092C4();
#endif

s32 fn_801CE540(s8 *arg0) {
    s32 var_r5;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_r4 != NULL) {
        var_r5 = M2C_FIELD(temp_r4, s32 *, 0x3F0);
    } else {
        var_r5 = 0;
    }
    if (var_r5 != 0) {
        if ((s32) (M2C_FIELD(arg0, s16 *, 6) * 0x64) < (s32) (M2C_FIELD(arg0, s16 *, 0xC) * 0x14)) {
            return 1;
        }
        if (fn_801092C4(var_r5 + 0x110) != 0) {
            return 1;
        }
        goto block_8;
    }
block_8:
    return 0;
}
