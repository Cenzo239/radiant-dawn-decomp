#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_801D0C68(u8 *arg0, s32 arg1) {
    s32 *t;
    t = *(s32 **)(arg0 + 0x18);
    *t = arg1;
    *(s32 **)(arg0 + 0x18) = t + 1;
    arg0[0x1D] = arg0[0x1D] + 1;
}
