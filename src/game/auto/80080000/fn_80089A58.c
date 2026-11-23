#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8023FC00();
M2C_UNK fn_8023FC0C();

s32 fn_80089A58(s8 *arg0) {
    fn_8023FC00();
    fn_8023FC0C();
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 4);
    return 1;
}
