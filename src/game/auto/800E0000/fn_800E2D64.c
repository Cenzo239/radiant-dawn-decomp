#include "game/auto/m2c_prelude.h"
s32 fn_800E2D64(s8 *arg0) {
    u8 temp_r3;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0x30);
    temp_r3 = M2C_FIELD(temp_r4, u8 *, 0xC);
    if ((s32) temp_r3 > 0) {
        M2C_FIELD(temp_r4, u8 *, 0xC) = (u8) (temp_r3 - 1);
        return 1;
    }
    return 0;
}
