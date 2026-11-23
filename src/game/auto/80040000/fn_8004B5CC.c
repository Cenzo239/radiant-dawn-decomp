#include "game/auto/m2c_prelude.h"
extern u8 lbl_803CA870[0x130];

void fn_8004B5CC(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(lbl_803CA870, s32 *, 4);
}
