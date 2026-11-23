#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_801C0638(s32, s8, s8, s8, s8, s32, f32, f32);

void fn_801C6E64(
#if TARGET_PC
s8 *arg0, s8 arg1, s8 arg2, s8 arg3, s8 arg4, s32 arg5, f32 arg6, f32 arg7
#else
s32 arg0, s8 arg1, s8 arg2, s8 arg3, s8 arg4, s32 arg5, f32 arg6, f32 arg7
#endif
) {
    fn_801C0638(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

