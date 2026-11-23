#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80165F94(void *, int, int);
FE10_PROTO void fn_8016F488(void *, int, int, unsigned char, unsigned int, int, unsigned char, int);
#else
M2C_UNK fn_80165F94();
M2C_UNK fn_8016F488();
#endif

void fn_8016F9C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    fn_80165F94(arg0, 6, arg7);
    fn_8016F488(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
