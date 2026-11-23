#include "game/auto/m2c_prelude.h"
s32 fn_8004A3EC(s8 *arg0) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0xC);
    if ((s32) temp_r0 >= 0x5B) {
        goto block_4;
    }
    if ((s32) temp_r0 >= 0x53) {
        goto block_6;
    }
    if ((s32) temp_r0 >= 0x50) {
        goto block_5;
    }
    goto block_6;
block_4:
    if ((s32) temp_r0 >= 0x60) {
        goto block_6;
    }
block_5:
    return 1;
block_6:
    return 0;
}
