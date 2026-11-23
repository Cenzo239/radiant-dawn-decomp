#include "game/auto/m2c_prelude.h"
u32 fn_80109030(s8 *arg0) {
    s32 temp_r4;

    temp_r4 = ((u16) M2C_FIELD(arg0, u16 *, 2) >> 5U) & 7;
    return (u32) ((7 - temp_r4) | (temp_r4 - 7)) >> 0x1FU;
}
