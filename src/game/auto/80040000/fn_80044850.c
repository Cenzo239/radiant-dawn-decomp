#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_8023F9F4(void*);
s32 fn_8027D6C4();
void fn_800763E0(void*);
void fn_80092BF8();
void fn_8023F4EC(void*);
void fn_802525A0(int, f32);
void fn_802573EC();
extern u8 lbl_80361684[0xbc];
extern f32 lbl_804CCDF8;
void fn_80044850(void) {
    if ((u32)fn_8023F9F4(lbl_80361684 + 0x62) != 0x40000U) {
        fn_800763E0(lbl_80361684 + 0x62);
    }
    fn_80092BF8();
    fn_8023F4EC(lbl_80361684 + 0x7B);
    if (fn_8027D6C4() == 0) {
        fn_802525A0(3, lbl_804CCDF8);
    }
    fn_802573EC();
}
