#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80026CD8(void *, void *, char);
FE10_PROTO void fn_8002C474(void *, char);
FE10_PROTO void fn_8006625C(void *, char, char, unsigned int);
#else
M2C_UNK fn_80026CD8();
M2C_UNK fn_8002C474();
M2C_UNK fn_8006625C();
#endif
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CB770[0x10];

s32 fn_801C85D0(void) {
    fn_80026CD8(lbl_803C8E80, M2C_FIELD(lbl_803CA870, s32 *, 0), -1);
    fn_8002C474(lbl_803C8E80, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE));
    fn_8006625C(lbl_803CB770, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x13), (s8) M2C_FIELD(lbl_803CA870, u8 *, 0x14), 0xD);
    return 1;
}
