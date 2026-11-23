#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32* fn_8010AF20(int);
s32
#if TARGET_PC
*
#endif
fn_800E1FA0(u8 *arg0) {
    s16 v = *(s16*)(arg0 + 0x12);
    s32 *t;
    if (v >= 0) {
        t = fn_8010AF20(v);
        if (t != NULL) {
            return t[1];
        }
    }
    return 0;
}
