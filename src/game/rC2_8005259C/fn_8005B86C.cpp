#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005B86C(void* proc) {
    Spr* s = fn_801E5640(proc, -0x1000, 0);
    if (s) {
        fn_801E5558(proc, s, 0);
    }
    fn_801FBE14(proc);
}
