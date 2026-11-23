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
fn_8001D3EC(
#if TARGET_PC
void *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
#if TARGET_PC
    void *sp8;
#else
    s32 sp8;
#endif

    sp8 = 0;
    fn_800068EC(&sp8, arg0, arg1);
    return sp8;
}
