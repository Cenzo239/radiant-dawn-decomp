#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80306B04();
extern u8 lbl_804CB0E6;

void fn_80021C74(s32 arg0) {
    if ((s32) lbl_804CB0E6 != arg0) {
        fn_80306B04((u8) arg0);
        lbl_804CB0E6 = (u8) arg0;
    }
}
