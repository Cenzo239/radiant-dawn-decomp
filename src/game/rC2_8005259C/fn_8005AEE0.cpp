#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005AEE0(void) {
    fn_801B5D30();
    fn_80114D00(lbl_803EC898);
    fn_801484B4(0);
}

extern "C" void fn_8005AF14(Obj4CB2* p) {
    void* q;
    void* r;
    while (lbl_804CB818) {
        fn_8012FCC0();
    }
    fn_80280EE0(fn_801930DC(fn_801856C8()));
    q = p->p4c;
    fn_80083E18(q, 0);
    fn_80083DC4(q, 0);
    r = fn_800D4228(lbl_80361F9C + 0x15);
    if (r) {
        fn_800D3C90(r, 4);
    }
}
