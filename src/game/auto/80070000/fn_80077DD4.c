#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern s8 *lbl_804CB598;
#else
extern s32 lbl_804CB598;
#endif

s32
#if TARGET_PC
*
#endif
fn_80077DD4(void) {
    return lbl_804CB598;
}
