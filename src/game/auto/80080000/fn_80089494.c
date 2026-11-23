#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8031DD0C();
extern u8 lbl_80380888[0x18];
extern void *lbl_803E4E88[8];

void fn_80089494(void) {
    lbl_803E4E88[0] = lbl_80380888;
    fn_8031DD0C(&lbl_803E4E88[1], lbl_80380888);
}

