#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80026CD8(void *, void *, char);
FE10_PROTO void fn_8002C0EC(void *, char);
FE10_PROTO void fn_8006C794(void *);
FE10_PROTO void fn_800E8EAC(char, char, void *);
#else
M2C_UNK fn_80026CD8();
M2C_UNK fn_8002C0EC();
M2C_UNK fn_8006C794();
M2C_UNK fn_800E8EAC();
#endif
extern u8 lbl_803C8E80[0x1648];
struct S870 { s32 a; s32 b; u8 pad[6]; u8 c; u8 pad1[4]; s8 d; s8 e; u8 pad2[0x11a]; };
extern struct S870 lbl_803CA870;

s32 fn_801C9BC8(s32 arg0) {
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.a, -1);
    fn_8002C0EC(lbl_803C8E80, (s8) lbl_803CA870.c);
    fn_8006C794(lbl_803C8E80);
    fn_800E8EAC(lbl_803CA870.d, lbl_803CA870.e, arg0);
    return 1;
}

