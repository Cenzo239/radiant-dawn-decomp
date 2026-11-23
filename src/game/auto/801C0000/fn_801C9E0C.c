#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80026CD8(void *, void *, char);
FE10_PROTO void fn_8002C0EC(void *, char);
FE10_PROTO void fn_8006C794(void *);
FE10_PROTO void fn_800E73F8(void *, void (*)(void *));
FE10_PROTO void fn_80108CC0(void *, void *, unsigned char);
#else
M2C_UNK fn_80026CD8();
M2C_UNK fn_8002C0EC();
M2C_UNK fn_8006C794();
M2C_UNK fn_800E73F8();
M2C_UNK fn_80108CC0();
#endif
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];

s32 fn_801C9E0C(s32 arg0) {
    fn_80026CD8(lbl_803C8E80, M2C_FIELD(lbl_803CA870, s32 *, 0), -1);
    fn_8002C0EC(lbl_803C8E80, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE));
    fn_8006C794(lbl_803C8E80);
    fn_80108CC0(lbl_803C8E80 + 0x110, lbl_803C8E80, 4);
    fn_800E73F8(arg0, 0);
    return 0;
}
