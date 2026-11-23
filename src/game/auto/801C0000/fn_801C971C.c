#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80026CD8(void *, void *, char);
FE10_PROTO void fn_8002C0EC(void *, char);
FE10_PROTO void fn_8006C794(void *);
FE10_PROTO void fn_800E8BE8(char, char, void *);
FE10_PROTO void fn_80114D00(void *);
FE10_PROTO void fn_80126EB0(void *, char, char);
#else
M2C_UNK fn_80026CD8();
M2C_UNK fn_8002C0EC();
M2C_UNK fn_8006C794();
M2C_UNK fn_800E8BE8();
M2C_UNK fn_80114D00();
M2C_UNK fn_80126EB0();
#endif
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803EC898[0x15867];

s32 fn_801C971C(s32 arg0) {
    s32 a;
    s32 b;
    fn_80126EB0(M2C_FIELD(lbl_803CA870, s32 *, 0), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x13), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x14));
    fn_80114D00(lbl_803EC898);
    fn_80026CD8(lbl_803C8E80, M2C_FIELD(lbl_803CA870, s32 *, 0), -1);
    fn_8002C0EC(lbl_803C8E80, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE));
    fn_8006C794(lbl_803C8E80);
    a = M2C_FIELD(lbl_803CA870, s8 *, 0x13);
    b = M2C_FIELD(lbl_803CA870, s8 *, 0x14);
    fn_800E8BE8(a, b, arg0);
    return 0;
}

