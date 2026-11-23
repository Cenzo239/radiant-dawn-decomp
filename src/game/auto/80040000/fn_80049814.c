#include "game/auto/m2c_prelude.h"
extern s32 lbl_804CB700;

void fn_80049814(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) (lbl_804CB700 & 4);
    lbl_804CB700 |= 4;
}
