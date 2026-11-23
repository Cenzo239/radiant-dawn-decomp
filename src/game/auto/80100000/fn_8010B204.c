#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7A4;
#else
extern s32 lbl_804CB7A4;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B204(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return lbl_804CB7A4 + ((arg0 - 1) * 0x50);
}
