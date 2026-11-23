#include "game/auto/m2c_prelude.h"
u32 fn_80109014(s8 *arg0) {
    s32 temp_r4;

    temp_r4 = ((u16) M2C_FIELD(arg0, u16 *, 2) >> 2U) & 7;
    return (u32) ((4 - temp_r4) | (temp_r4 - 4)) >> 0x1FU;
}
