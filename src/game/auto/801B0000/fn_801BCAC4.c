#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800E24F8(char *);
#else
M2C_UNK fn_800E24F8();
#endif
extern u8 lbl_8036E118[0x2c8];

void fn_801BCAC4(void) {
    fn_800E24F8(lbl_8036E118);
    fn_800E24F8(lbl_8036E118 + 0xA);
    fn_800E24F8(lbl_8036E118 + 0x15);
}
