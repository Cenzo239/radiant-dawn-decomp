#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void
#if TARGET_PC
*
#endif
fn_80062598(void* a, void* p) {
    if (fn_8013B9A8()) {
        if (p == 0) {
            fn_8013B974(fn_80068E00());
        } else {
#if TARGET_PC
            return fn_800811E4(lbl_8037F7B0, p);
#else
            fn_800811E4(lbl_8037F7B0, p);
#endif
        }
    }
#if TARGET_PC
    return 0;
#endif
}
