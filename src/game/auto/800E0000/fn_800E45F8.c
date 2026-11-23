#include "game/auto/m2c_prelude.h"
s32 fn_800E45F8(s8 *arg0, u16 *arg1) {
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0x30);
    if ((u16) *arg1 == (u16) M2C_FIELD(temp_r5, u16 *, 4)) {
        M2C_FIELD(temp_r5, u16 *, 4) = 0U;
    }
    return 0;
}
