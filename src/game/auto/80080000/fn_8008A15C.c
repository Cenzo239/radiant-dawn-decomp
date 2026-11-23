#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80089EF0();
s32 fn_80246510();
extern s16 lbl_804CA3C8;
extern s32 lbl_804CB700;

void fn_8008A15C(void) {
    if ((fn_80246510() != 0) && !(lbl_804CB700 & 0x100) && ((s16) lbl_804CA3C8 >= 0)) {
        fn_80089EF0();
    }
}
