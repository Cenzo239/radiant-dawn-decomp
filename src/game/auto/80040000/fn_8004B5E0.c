#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
#else
M2C_UNK fn_800453B4();
#endif
extern u8 lbl_803CA870[0x130];

s32 fn_8004B5E0(void) {
    fn_800453B4(lbl_803CA870, 0);
    return 9;
}
