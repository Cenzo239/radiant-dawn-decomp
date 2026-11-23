#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_800CDF54();

s32 fn_800898B4(s8 *arg0) {
    s8 *temp_r4;
    s32 v;

    temp_r4 = M2C_FIELD(arg0, s8 **, 4);
    v = M2C_FIELD(temp_r4, s32 *, 4);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r4 + 8);
    fn_800CDF54(v, temp_r4, arg0);
    return 1;
}

