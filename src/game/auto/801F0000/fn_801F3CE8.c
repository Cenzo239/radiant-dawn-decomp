#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800659B0(void *, unsigned char, char, char);
FE10_PROTO void fn_801E5880(void *);
#else
M2C_UNK fn_800659B0();
M2C_UNK fn_801E5880();
#endif

void fn_801F3CE8(s32 arg0, s32 arg1, s32 arg2) {
    fn_800659B0(arg0, 0xCC, -1, -1);
    fn_801E5880(arg0);
}

