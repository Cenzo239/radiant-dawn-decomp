#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80053490(void* p) {
    switch (lbl_803CA870.b0c) {
    case 0x33:
    case 0x34:
        fn_80083DC4(p, 8);
        return;
    }
    fn_800466B4(&lbl_803CA870, p);
}

extern "C" void fn_800534C8(void) {
    fn_8004559C(&lbl_803CA870, 1);
}

extern "C" void fn_800534D8(void* p) {
    u64 f;
    Unit2* u = (Unit2*)lbl_803CA870.unit;
    f = u->flags108;
    if (!(f & 1)) {
        u->flags108 = f | 1;
        if (fn_80060728(&lbl_803CAB38)->c2 != 0 ||
            (fn_80060728(&lbl_803CAB38)->b18 != 1 && fn_80067880(0) == 0)) {
            fn_80193014();
            fn_80081A90(p);
        }
    }
}
