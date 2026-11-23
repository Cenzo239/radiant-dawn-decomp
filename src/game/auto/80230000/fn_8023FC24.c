#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8031DD0C();
extern u8 lbl_80380888[0x18];
extern u8 lbl_8042549C[0x100];

void fn_8023FC24(void) {
    M2C_FIELD(lbl_8042549C, u8 **, 0) = lbl_80380888;
    fn_8031DD0C(lbl_8042549C + 4, lbl_80380888);
}
