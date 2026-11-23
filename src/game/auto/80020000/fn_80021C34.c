#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8030385C();
extern u8 lbl_804CB0E5;

void fn_80021C34(s32 arg0) {
    if ((s32) lbl_804CB0E5 != arg0) {
        fn_8030385C((u8) arg0);
        lbl_804CB0E5 = (u8) arg0;
    }
}
