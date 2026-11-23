#include "game/auto/m2c_prelude.h"
extern s32 lbl_804CB7D0;
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7D4;
#else
extern s32 lbl_804CB7D4;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B0CC(s32 arg0) {
    if (arg0 < 0) {
        return 0;
    }
    if (arg0 >= (s32) lbl_804CB7D0) {
        return 0;
    }
    return lbl_804CB7D4 + (arg0 * 0xB4);
}
