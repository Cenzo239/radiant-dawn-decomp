#include "game/auto/m2c_prelude.h"
extern u8 lbl_80387928[0xac];

void fn_80175E40(void) {
    M2C_FIELD(lbl_80387928, s32 *, 0x3C) = 0x3C100A;
    M2C_FIELD(lbl_80387928, s32 *, 0x78) = 0x3C100A;
}
