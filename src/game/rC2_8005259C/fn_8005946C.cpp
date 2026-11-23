#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005946C(void* p) {
    if (!lbl_804CB818) fn_8012FCB0();
    fn_801856F4();
    LAZY1(lbl_804CB440, lbl_804CB444, lbl_8037EC08);
    LAZY1(lbl_804CB448, lbl_804CB44C, lbl_8037EBB0);
    LAZY2(lbl_804CB450, lbl_804CB458, lbl_8037E178, lbl_8037F16C);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB458, p, 0);
    SALLY_TAIL(p);
}
