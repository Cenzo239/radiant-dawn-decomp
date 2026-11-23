#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO void fn_80049EEC(int, int);
#else
M2C_UNK fn_800453B4();
M2C_UNK fn_80049EEC();
#endif
extern u8 lbl_803CA870[0x130];

s32 fn_801C83F0(s32 arg0) {
    fn_80049EEC(lbl_803CA870, arg0);
    fn_800453B4(lbl_803CA870, 0x4F);
    return 1;
}
