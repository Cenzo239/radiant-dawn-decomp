#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80307824(u32);
extern u32 lbl_804CB0BC;

void fn_800217CC(u32 arg0) {
    if ((u32) lbl_804CB0BC != arg0) {
        fn_80307824(arg0);
        lbl_804CB0BC = arg0;
    }
}
