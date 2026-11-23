#include "game/auto/m2c_prelude.h"
s32 fn_801D04E4(s8 *arg0) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 1);
    if ((s32) temp_r0 == 5) {
        goto block_6;
    }
    if ((s32) temp_r0 >= 5) {
        goto block_4;
    }
    if ((s32) temp_r0 >= 2) {
        goto block_5;
    }
    goto block_6;
block_4:
    if ((s32) temp_r0 >= 7) {
        goto block_6;
    }
block_5:
    return 1;
block_6:
    return 0;
}
