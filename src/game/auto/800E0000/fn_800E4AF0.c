#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_800E4AF0(u8 *arg0, int arg1) {
    if (arg1 < 0) {
        arg1 = 0x3C;
    }
    (*(u8 **)(arg0 + 0x30))[0x12] = arg1;
    (*(u8 **)(arg0 + 0x30))[0x11] = 0;
    (*(u8 **)(arg0 + 0x30))[0x13] = 1;
}
