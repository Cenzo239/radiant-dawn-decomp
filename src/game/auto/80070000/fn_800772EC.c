#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8031DD0C();
extern u8 lbl_80380888[0x18];
extern u8 lbl_803CD828[0x100];

void fn_800772EC(void) {
    M2C_FIELD(lbl_803CD828, u8 **, 0) = lbl_80380888;
    fn_8031DD0C(lbl_803CD828 + 4, lbl_80380888);
}
