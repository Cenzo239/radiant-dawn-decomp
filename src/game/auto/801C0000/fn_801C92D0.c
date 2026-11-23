#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80026C44(void *, void *, void *);
FE10_PROTO void fn_8002C0EC(void *, char);
FE10_PROTO unsigned char * fn_80044FD0(char *);
FE10_PROTO void fn_8006C794(void *);
FE10_PROTO void fn_80108C80(void *, void *, unsigned char);
FE10_PROTO void fn_801C89B4(void *, void *, int);
#else
M2C_UNK fn_80026C44();
M2C_UNK fn_8002C0EC();
s32 * fn_80044FD0();
M2C_UNK fn_8006C794();
M2C_UNK fn_80108C80();
M2C_UNK fn_801C89B4();
#endif
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];

s32 fn_801C92D0(s32 arg0) {
    fn_80026C44(lbl_803C8E80, M2C_FIELD(lbl_803CA870, s32 *, 0), M2C_FIELD(lbl_803CA870, s32 *, 4));
    fn_8002C0EC(lbl_803C8E80, (s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE));
    fn_80108C80(lbl_803C8E80 + 0x5B0, lbl_803C8E80 + 0x4A0, 7);
    fn_8006C794(lbl_803C8E80);
    fn_801C89B4(*fn_80044FD0(lbl_803CA870), arg0, 0);
    return 0;
}
