#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO extern u8 *lbl_804CB7AC;
#else
extern s32 lbl_804CB7AC;
#endif

s32
#if TARGET_PC
*
#endif
fn_8010B22C(s32 arg0) {
    return lbl_804CB7AC + (arg0 * 0x2C);
}
