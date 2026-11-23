#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(char *);
#else
M2C_UNK fn_800D0864();
#endif

void
#if TARGET_PC
*
#endif
fn_8008DB4C(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
#if TARGET_PC
    return fn_800D0864(arg0 + (arg1 << 5));
#else
    fn_800D0864(arg0 + (arg1 << 5));
#endif
}
