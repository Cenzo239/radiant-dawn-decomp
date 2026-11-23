#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005D828(void) {
    fn_80062380(&lbl_803CAB38, (u8*)&lbl_803CAB38 + 0x914);
}

extern "C" void fn_8005D838(void) {
    Unit2* n;
    Unit2* u;
    fn_80062454(&lbl_803CAB38);
    fn_8012D620();
    fn_8012D908();
    u = *(Unit2**)(lbl_804CB814 + 4);
    while (u) {
        n = u->next4;
        if (fn_8011B77C(u->x12c, lbl_804CA4D8)) {
            fn_800FAFF0(u, 0);
            fn_8012FF30();
            break;
        }
        u = n;
    }
}
