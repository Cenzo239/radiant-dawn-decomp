#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800310E4(char *, unsigned char, int, unsigned int);
FE10_PROTO unsigned char * fn_80044FD0(char *);
FE10_PROTO char * fn_80110F08(void *);
#else
M2C_UNK fn_800310E4();
M2C_UNK fn_80044FD0();
M2C_UNK fn_80110F08(M2C_UNK);
#endif
extern u8 lbl_803CA870[0x130];

void fn_80044C28(void) {
    fn_800310E4(fn_80110F08(fn_80044FD0(lbl_803CA870)), 0, 0x28, 0);
}

