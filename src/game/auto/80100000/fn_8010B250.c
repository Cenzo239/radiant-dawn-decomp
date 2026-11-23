#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7D8;
#else
extern s32 lbl_804CB7D8;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B250(s32 arg0) {
    return lbl_804CB7D8 + (arg0 * 0xC);
}
