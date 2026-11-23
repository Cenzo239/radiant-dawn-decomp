#include "game/auto/m2c_prelude.h"
M2C_UNK fn_803045DC(u32);
extern u32 lbl_804CB0DC;

void fn_80021B68(u32 arg0) {
    if (arg0 != (u32) lbl_804CB0DC) {
        fn_803045DC(arg0);
        lbl_804CB0DC = arg0;
    }
}
