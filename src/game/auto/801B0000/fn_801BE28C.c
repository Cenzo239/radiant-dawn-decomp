#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_803080DC(unsigned int, unsigned int, unsigned int, unsigned int);
#else
M2C_UNK fn_803080DC();
#endif

void fn_801BE28C(
#if TARGET_PC
void *arg0, s8 *arg1
#else
s32 arg0, s8 *arg1
#endif
) {
    fn_803080DC(M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4), M2C_FIELD(arg1, s16 *, 6));
}

