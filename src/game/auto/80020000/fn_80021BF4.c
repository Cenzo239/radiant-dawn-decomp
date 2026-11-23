#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80307274();
extern u8 lbl_804CB0E4;

void fn_80021BF4(s32 arg0) {
    if ((s32) lbl_804CB0E4 != arg0) {
        fn_80307274((u8) arg0);
        lbl_804CB0E4 = (u8) arg0;
    }
}
