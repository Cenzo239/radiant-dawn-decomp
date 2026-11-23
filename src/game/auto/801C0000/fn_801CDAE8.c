#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800E24F8(char *);
#else
M2C_UNK fn_800E24F8();
#endif
extern u8 lbl_8036EA00[0x40];

void fn_801CDAE8(void) {
    fn_800E24F8(lbl_8036EA00 + 7);
}
