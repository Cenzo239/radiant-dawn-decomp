#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO void fn_8004AAF0(int);
#else
M2C_UNK fn_800453B4();
M2C_UNK fn_8004AAF0();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80025950(s32 arg0) {
    fn_800453B4(lbl_803CA870, 1);
    fn_8004AAF0(arg0);
}
