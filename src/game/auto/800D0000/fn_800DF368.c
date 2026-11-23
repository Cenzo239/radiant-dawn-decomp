#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int * fn_800E45B0(int);
#else
s8 * fn_800E45B0();
#endif

s32 fn_800DF368(s32 arg0, s32 arg1) {
    s32 *temp_r3;
    s8 *temp_r4;
    s8 *temp_r4_2;
    s8 *var_r3;

    if (arg0 == 0) {
        var_r3 = NULL;
    } else if ((u32) arg0 >= 0x10000U) {
        var_r3 = NULL;
    } else {
        var_r3 = fn_800E45B0((u16) arg0);
    }
    if (var_r3 == NULL) {
        return 0;
    }
    temp_r4 = M2C_FIELD(var_r3, s8 **, 0x30);
    temp_r3 = M2C_FIELD(temp_r4, s32 **, 0);
    temp_r4_2 = temp_r4 + 0x18;
    if (arg1 != 0) {
        if (temp_r4_2 != NULL) {
            M2C_FIELD(temp_r4, s32 *, 0x18) = (s32) (M2C_FIELD(temp_r4, s32 *, 0x18) | 4);
        }
        if (temp_r3 != NULL) {
            *temp_r3 |= 0x18;
        }
    } else {
        if (temp_r4_2 != NULL) {
            M2C_FIELD(temp_r4, s32 *, 0x18) = (s32) (M2C_FIELD(temp_r4, s32 *, 0x18) & 0xFFFFFFFB);
        }
        if (temp_r3 != NULL) {
            *temp_r3 &= 0xFFFFFFE7;
        }
    }
    return 1;
}
