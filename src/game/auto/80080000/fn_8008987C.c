#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80177284(int, void *, ...);
#else
M2C_UNK fn_80177284();
#endif

s32 fn_8008987C(s8 *arg0) {
    s8 *temp_r5;
    s32 v;

    temp_r5 = M2C_FIELD(arg0, s8 **, 4);
    v = M2C_FIELD(temp_r5, s32 *, 4);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r5 + 8);
    fn_80177284(v, arg0, temp_r5);
    return 1;
}

