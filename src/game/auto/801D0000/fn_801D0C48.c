#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_801D0C48(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s32 *t = *(s32 **)(arg0 + 0x18);
    *t = arg1;
    *(s32 **)(arg0 + 0x18) = t + 1;
    *(u8 *)(arg0 + 0x1D) = *(u8 *)(arg0 + 0x1D) + 1;
}
