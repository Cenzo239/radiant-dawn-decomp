#include "game/auto/m2c_prelude.h"
M2C_UNK memcpy();

void fn_8008A780(
#if TARGET_PC
s8 *arg0, s32 arg1, void *arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
    memcpy(M2C_FIELD(arg0, s32 *, 4), arg2, arg1);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + arg1);
}
