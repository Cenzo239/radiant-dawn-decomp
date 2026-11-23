#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_80018208(void *, int);
FE10_PROTO void fn_80018888(unsigned int *, int);
#else
s32 fn_80018208();
M2C_UNK fn_80018888();
#endif

void fn_800183F0(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    if (fn_80018208(arg0, 1) == 0) {
        fn_80018888(arg0, 1);
    }
}

