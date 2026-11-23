#include "game/auto/m2c_prelude.h"
extern u8 lbl_803E4EF8[0x130];
extern M2C_UNK *lbl_804CB608;

void fn_8008E398(void) {
    M2C_FIELD(lbl_803E4EF8, s32 *, 0x124) = 0;
    M2C_FIELD(lbl_803E4EF8, s32 *, 0x120) = 0;
    lbl_804CB608 = lbl_803E4EF8;
}
