#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_801036D0(s8*, void *, s32, s32, void *);
FE10_PROTO void fn_8011E300(void *, char, char, int);
#else
void fn_801036D0(s8*, s32, s32, s32, s32);
M2C_UNK fn_8011E300();
#endif
extern u8 lbl_803CA870[0x130];

void fn_800472BC(s32 arg0) {
    s32 temp_r29;
    s32 a;
    s32 b;

    temp_r29 = M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 0), s32 *, 0xF8);
    M2C_FIELD(lbl_803CA870, s32 *, 4) = temp_r29;
    fn_8011E300(M2C_FIELD(lbl_803CA870, s8 **, 0), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x13), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x14), 1);
    a = M2C_FIELD(lbl_803CA870, s8 *, 0x13);
    b = M2C_FIELD(lbl_803CA870, s8 *, 0x14);
    fn_801036D0(M2C_FIELD(lbl_803CA870, s8 **, 0), temp_r29, a, b, arg0);
}

