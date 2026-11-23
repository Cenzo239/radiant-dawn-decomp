#include "game/auto/m2c_prelude.h"
s32 fn_8001F060(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r5;
    s32 temp_r7;

    temp_r7 = arg2 >> 1;
    temp_r5 = arg3 % arg2;
    if (temp_r5 < temp_r7) {
        return arg0 + ((s32) (temp_r5 * (arg1 - arg0)) / temp_r7);
    }
    return arg1 + ((s32) ((temp_r5 - temp_r7) * (arg0 - arg1)) / temp_r7);
}
