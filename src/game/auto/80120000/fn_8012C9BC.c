#include "game/auto/m2c_prelude.h"
s32 fn_8012C9BC(s8 *arg0, u32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_7;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x1BC);
    if (temp_r0 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0 != arg1) {
        goto block_3;
    }
    return 0;
block_3:
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0x1E4);
    if (temp_r0_2 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_2 != arg1) {
        goto block_6;
    }
    return 1;
block_6:
    temp_r0_3 = M2C_FIELD(arg0, s32 *, 0x20C);
    if (temp_r0_3 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_3 != arg1) {
        goto block_9;
    }
    return 2;
block_9:
    temp_r0_4 = M2C_FIELD(arg0, s32 *, 0x234);
    if (temp_r0_4 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_4 != arg1) {
        goto block_12;
    }
    return 3;
block_12:
    temp_r0_5 = M2C_FIELD(arg0, s32 *, 0x25C);
    if (temp_r0_5 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_5 != arg1) {
        goto block_15;
    }
    return 4;
block_15:
    temp_r0_6 = M2C_FIELD(arg0, s32 *, 0x284);
    if (temp_r0_6 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_6 != arg1) {
        goto block_18;
    }
    return 5;
block_18:
    temp_r0_7 = M2C_FIELD(arg0, s32 *, 0x2AC);
    if (temp_r0_7 == 0) {
        goto block_21;
    }
    if ((u32) temp_r0_7 != arg1) {
        goto block_21;
    }
    return 6;
block_21:
    return -1;
}
