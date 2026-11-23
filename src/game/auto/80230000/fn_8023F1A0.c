#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8023C9C8(char *, s32);
#else
M2C_UNK fn_8023C9C8(s32, s32);
#endif

void fn_8023F1A0(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
    fn_8023C9C8(arg0, arg1);
}
