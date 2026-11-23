#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

/* lbl_804CB700 is read twice before either test, so the CSE-defeating volatile access is required to match. */
#define VF (*(volatile u32*)&lbl_804CB700)
extern "C" void fn_80057CBC(void) {
    if (fn_80068D74()) {
        u32 a = VF;
        int t = 0;
        u32 b = VF;
        if ((a & 0x10) && !(b & 0x20)) {
            t = 1;
        }
        if (!t) {
            fn_80131DE4();
        }
        fn_80133034();
    }
}

extern "C" void fn_80057D14(void) {
    if (fn_80068D74()) {
        fn_80131DE4();
        fn_80133034();
    }
}
