#include "game/auto/m2c_prelude.h"
s32 fn_800C7F90();

s32 fn_8008961C(s8 *arg0) {
    if (fn_800C7F90() != 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 4);
    return 1;
}
