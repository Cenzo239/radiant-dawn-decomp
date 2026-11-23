#include "game/auto/m2c_prelude.h"
extern s32 lbl_804CB700;

void fn_80049830(s8 *arg0) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0x60) == 0) {
        lbl_804CB700 &= 0xFFFFFFFB;
    }
}
