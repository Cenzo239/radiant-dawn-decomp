#include "game/auto/m2c_prelude.h"
extern u8 lbl_803CA870[0x130];

void fn_8004A6F4(void) {
    M2C_FIELD(lbl_803CA870, s8 *, 0x17) = 0;
    M2C_FIELD(lbl_803CA870, s8 *, 0x28) = 0;
}
