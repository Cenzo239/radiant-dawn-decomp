#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801BDF20(char *, s32, s32, s32);
#else
M2C_UNK fn_801BDF20(s32, s32, s32, s32);
#endif

void fn_801C6D9C(
#if TARGET_PC
s8 *arg0, s32 arg1, s32 arg2, s32 arg3
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3
#endif
) {
    fn_801BDF20(arg0, arg1, arg2, arg3);
}
