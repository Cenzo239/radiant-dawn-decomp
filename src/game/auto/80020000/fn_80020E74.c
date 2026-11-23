#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB0A8;
#else
extern s32 lbl_804CB0A8;
#endif

s32
#if TARGET_PC
*
#endif
fn_80020E74(void) {
    return lbl_804CB0A8;
}
