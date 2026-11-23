#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO void fn_80068E0C(void *, void *);
#else
M2C_UNK fn_800453B4();
M2C_UNK fn_80068E0C(s32, s32);
#endif
extern u8 lbl_803CA870[0x130];

void fn_8004B610(s32 arg0, s32 arg1) {
    fn_80068E0C(arg0, arg1);
    fn_800453B4(lbl_803CA870, 0xF);
}
