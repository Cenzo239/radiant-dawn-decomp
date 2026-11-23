#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO M2C_UNK fn_8016B90C(void *, s32, void *, void *);
#else
M2C_UNK fn_8016B90C(s32, s32, s32, s32);
#endif

void fn_8016BE00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    fn_8016B90C(arg0, arg1, arg2, arg3);
}
