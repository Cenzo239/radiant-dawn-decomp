#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_80007630(void *, char *);
FE10_PROTO void fn_800106AC(int, void *, void *);
#else
s32 fn_80007630();
M2C_UNK fn_800106AC();
#endif
extern u8 fn_8017CD80[0x3fc];
extern u8 lbl_8036B4C8[0x150];
extern u8 lbl_804CB8CA;

void fn_8017D17C(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    if ((fn_80007630(arg0, lbl_8036B4C8 + 0xC3) >= 0) && ((s8) lbl_804CB8CA != 0)) {
        fn_800106AC(5, fn_8017CD80, arg0);
    }
}

