#include "game/auto/m2c_prelude.h"
extern s32 lbl_804CB7C8;
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7CC;
#else
extern s32 lbl_804CB7CC;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010AF20(s32 arg0) {
    if ((s32) lbl_804CB7C8 < arg0) {
        return 0;
    }
    return lbl_804CB7CC + (arg0 * 0x18);
}
