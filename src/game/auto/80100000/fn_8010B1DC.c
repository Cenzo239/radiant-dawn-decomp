#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB79C;
#else
extern s32 lbl_804CB79C;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B1DC(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return lbl_804CB79C + ((arg0 - 1) * 0x11C);
}
