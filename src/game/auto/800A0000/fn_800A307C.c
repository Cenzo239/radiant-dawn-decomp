#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8014BED4(char *, void *, ...);
#else
M2C_UNK fn_8014BED4();
#endif
extern u8 lbl_80364C1C[0x424];
extern s32 lbl_804CB700;

void fn_800A307C(s32 arg0) {
    lbl_804CB700 |= 0x800;
    fn_8014BED4(lbl_80364C1C + 0xE5, arg0, lbl_80364C1C);
}
