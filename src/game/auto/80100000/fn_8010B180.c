#include "game/auto/m2c_prelude.h"
extern s32 lbl_804CB7DC;
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7E0;
#else
extern s32 lbl_804CB7E0;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B180(s32 arg0) {
    if (arg0 < 0) {
        return 0;
    }
    if (arg0 >= (s32) lbl_804CB7DC) {
        return 0;
    }
    return lbl_804CB7E0 + (arg0 * 0xC);
}
