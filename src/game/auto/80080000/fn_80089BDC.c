#include "game/auto/m2c_prelude.h"
extern u8 lbl_804CB5D0[0x8];

void fn_80089BDC(s8 *arg0) {
    M2C_FIELD(lbl_804CB5D0, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0);
    M2C_FIELD(lbl_804CB5D0, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
    M2C_FIELD(lbl_804CB5D0, u16 *, 4) = (u16) M2C_FIELD(arg0, u16 *, 4);
}
