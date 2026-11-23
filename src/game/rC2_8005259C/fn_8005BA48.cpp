#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005BA48(void* proc) {
    char buf[32];
    Spr* s = fn_801E5640(proc, -0x1000, 0);
    if (s) {
        fn_801E5558(proc, s, 0);
    }
    fn_80290D04(buf, 0x20, lbl_80361F9C + 0x10a, fn_8006074C(&lbl_803CAB38)->name);
    fn_80205778(proc, buf);
}
