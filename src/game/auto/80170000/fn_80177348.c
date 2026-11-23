#include "game/auto/m2c_prelude.h"
void fn_80177348(s8 *arg0) {
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0x30);
    M2C_FIELD(temp_r4, s32 *, 0x30) = (s32) (M2C_FIELD(temp_r4, s32 *, 0x30) - 1);
}
