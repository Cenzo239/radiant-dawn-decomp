#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A2C(void **);
#else
M2C_UNK fn_80006A2C();
#endif
extern s32 lbl_804CB700;

void fn_80175414(s32 arg0) {
    fn_80006A2C(arg0 + 0x30);
    lbl_804CB700 |= 0x10000000;
}
