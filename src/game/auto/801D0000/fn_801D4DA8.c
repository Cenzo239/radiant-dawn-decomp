#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_802428AC();
extern u8 lbl_803CAB38[0x988];
s32 fn_801D4DA8(u8 *arg0) {
    s32 r;
    s32 t;
    if (lbl_803CAB38[0x9D] != 0) {
        return 3;
    }
    t = fn_802428AC();
    arg0[4] = t;
    r = 2;
    if (t != 0) {
        r = 0;
    }
    return r;
}
