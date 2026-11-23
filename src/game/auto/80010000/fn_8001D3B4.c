#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800068EC(void **, void *, unsigned int);
#else
M2C_UNK fn_800068EC();
#endif

s32
#if TARGET_PC
*
#endif
fn_8001D3B4(
#if TARGET_PC
s8 *arg0
#else
s32 arg0
#endif
) {
#if TARGET_PC
    void *sp8;
#else
    s32 sp8;
#endif

    sp8 = 0;
    fn_800068EC(&sp8, arg0, 0);
    return sp8;
}
