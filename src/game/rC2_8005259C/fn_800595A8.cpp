#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_800595A8(void* p) {
    if (!lbl_804CB818) fn_8012FCB0();
    fn_801856F4();
    LAZY1(lbl_804CB41C, lbl_804CB420, lbl_8037EA50);
    LAZY1(lbl_804CB424, lbl_804CB428, lbl_8037E9F8);
    LAZY1(lbl_804CB42C, lbl_804CB430, lbl_8037E9A0);
    LAZY2(lbl_804CB434, lbl_804CB438, lbl_8037E168, lbl_8037F0D8);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB438, p, 0);
    SALLY_TAIL(p);
}
