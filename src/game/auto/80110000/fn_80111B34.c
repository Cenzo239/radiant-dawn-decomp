#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80110D38(void *);
#else
M2C_UNK fn_80110D38(s32);
#endif

s32
#if TARGET_PC
*
#endif
fn_80111B34(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    fn_80110D38(arg0);
    return arg0;
}
