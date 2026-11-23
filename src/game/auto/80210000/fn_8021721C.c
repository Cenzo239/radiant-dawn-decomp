#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80079210(void *);
#else
M2C_UNK fn_80079210(s32);
#endif

void fn_8021721C(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    fn_80079210(arg0);
}
