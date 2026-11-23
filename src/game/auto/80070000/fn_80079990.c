#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8031DD0C();
extern u8 lbl_80380888[0x18];
extern void *lbl_803CD8A8[8];

void fn_80079990(void) {
    lbl_803CD8A8[0] = lbl_80380888;
    fn_8031DD0C(&lbl_803CD8A8[1], lbl_80380888);
}

