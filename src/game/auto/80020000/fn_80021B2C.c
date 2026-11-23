#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80305794(s32);
extern u8 lbl_804CB0D8;

void fn_80021B2C(u8 arg0) {
    if (arg0 != (u8) lbl_804CB0D8) {
        fn_80305794(arg0);
        lbl_804CB0D8 = arg0;
    }
}
