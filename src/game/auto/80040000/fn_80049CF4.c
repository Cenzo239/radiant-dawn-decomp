#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800262A8(unsigned char *, unsigned int);
#else
s32 fn_800262A8();
#endif
#if TARGET_PC
FE10_PROTO void fn_80108A8C(void *, void *, int);
#else
M2C_UNK fn_80108A8C();
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_80049CF4(void) {
    if (fn_800262A8(lbl_803C8E80 + 0xDE0, 0x6E) != 0) {
        fn_80108A8C(lbl_803C8E80 + 0x5B0, lbl_803C8E80 + 0x4A0, 1);
        fn_80108A8C(M2C_FIELD(lbl_803C8E80, s8 **, 0x890) + 0x110, M2C_FIELD(lbl_803C8E80, s8 **, 0x890), 1);
    }
}
