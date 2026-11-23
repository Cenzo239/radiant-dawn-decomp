#include "game/auto/m2c_prelude.h"
f32 fn_8001EF44(s32 arg0, s32 arg1, f32 farg0, f32 farg1) {
    s32 temp_r0;
    s32 temp_r6;

    temp_r6 = arg0 >> 1;
    temp_r0 = arg1 % arg0;
    if (temp_r0 < temp_r6) {
        return farg0 + (((f32) temp_r0 * (farg1 - farg0)) / (f32) temp_r6);
    }
    return farg1 + (((f32) (temp_r0 - temp_r6) * (farg0 - farg1)) / (f32) temp_r6);
}
