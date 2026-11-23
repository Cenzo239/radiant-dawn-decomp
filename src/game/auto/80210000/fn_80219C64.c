#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80216F84(void *, void *);
#else
M2C_UNK fn_80216F84(s32);
#endif

void fn_80219C64(
#if TARGET_PC
void *arg0, void *arg1
#else
s32 arg0
#endif
) {
#if TARGET_PC
    fn_80216F84(arg0, arg1);
#else
    fn_80216F84(arg0);
#endif
}
