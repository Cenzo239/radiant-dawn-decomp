#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO int fn_800A04C8(void *, int, int, int);
#else
M2C_UNK fn_800453B4();
M2C_UNK fn_800A04C8();
#endif
extern u8 lbl_803CA870[0x130];

s32 fn_801C9C50(s32 arg0) {
    u8 temp_r30;

    temp_r30 = M2C_FIELD(lbl_803CA870, u8 *, 0xC);
    fn_800453B4(lbl_803CA870, 0U);
    fn_800A04C8(arg0, M2C_FIELD(lbl_803CA870, u8 *, 0xC), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x13), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x14));
    fn_800453B4(lbl_803CA870, temp_r30);
    return 1;
}
