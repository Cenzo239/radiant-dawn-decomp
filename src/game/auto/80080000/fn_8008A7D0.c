#include "game/auto/m2c_prelude.h"
M2C_UNK memset();

void fn_8008A7D0(s8 *arg0, s32 arg1, s32 arg2) {
    memset(M2C_FIELD(arg0, s32 *, 4), arg2, arg1);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + arg1);
}
