#include "game/auto/m2c_prelude.h"
extern u8 lbl_803C8E80[0x1648];

s8 *fn_8002C738(s8 *arg0) {
    if (!(M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) & 0x10)) {
        goto block_4;
    }
    if (M2C_FIELD(arg0, s32 *, 0x10C) & 0x40000) {
        goto block_6;
    }
    if (!(M2C_FIELD(arg0, s32 *, 0x5AC) & 0x40000)) {
        goto block_4;
    }
    return arg0 + 0x4A0;
block_4:
    return NULL;
block_6:
    return arg0;
}
