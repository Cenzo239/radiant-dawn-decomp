#include "game/auto/m2c_prelude.h"
extern u8 lbl_803C8E80[0x1648];

s32 fn_801D04D0(void) {
    return ((u32) M2C_FIELD(lbl_803C8E80, u32 *, 0x15EC) >> 8U) & 1;
}
