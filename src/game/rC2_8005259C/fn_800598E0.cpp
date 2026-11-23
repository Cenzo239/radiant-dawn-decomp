#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800598E0(Obj4CB2* p) {
    void* q;
    void* r;
    while (lbl_804CB818) {
        fn_8012FCC0();
    }
    fn_80280EE0(fn_801930DC(fn_801856C8()));
    q = p->p4c;
    fn_80083E18(q, fn_8005997C);
    fn_80083DC4(q, 1);
    r = fn_800D4228(lbl_80361F9C + 0x15);
    if (r) {
        fn_800D3C90(r, 4);
    }
    lbl_803CA870.x11 = -1;
    lbl_803CA870.y12 = -1;
}

extern "C" void fn_8005997C(void* p) {
    if (fn_80068D74()) {
        fn_800106AC(3, fn_800599C4, p);
    }
}
