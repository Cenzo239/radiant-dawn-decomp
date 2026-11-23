#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(char *, int);
#else
M2C_UNK fn_8023F1A0();
#endif
extern u8 lbl_8036B0D0[0xf];

void fn_80165718(void) {
    fn_8023F1A0(lbl_8036B0D0, 0xC20);
}
