#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800E5884(void *, void *, void *);
#else
M2C_UNK fn_800E5884();
#endif

void fn_800E5BB0(
#if TARGET_PC
void *arg0, s8 *arg1
#else
s32 arg0, s8 *arg1
#endif
) {
    fn_800E5884(arg0, 0, M2C_FIELD(arg1, s32 *, 0x3F0));
}

