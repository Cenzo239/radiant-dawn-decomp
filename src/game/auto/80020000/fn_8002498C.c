#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
#else
M2C_UNK fn_800453B4();
#endif
extern u8 lbl_803CA870[0x130];

s32 fn_8002498C(void) {
    fn_800453B4(lbl_803CA870, 0x83);
    return 5;
}
