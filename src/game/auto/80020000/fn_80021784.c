#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80307EF0(u32);
extern u32 lbl_804CB0B8;

void fn_80021784(u32 arg0) {
    if ((u32) lbl_804CB0B8 != arg0) {
        fn_80307EF0(arg0);
        lbl_804CB0B8 = arg0;
    }
}
