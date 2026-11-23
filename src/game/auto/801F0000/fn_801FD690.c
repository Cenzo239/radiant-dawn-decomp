#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_80105194(void *);
#if TARGET_PC
FE10_PROTO s32 fn_801F15A4(void *);
#else
s32 fn_801F15A4(s32);
#endif
void *fn_801059B0(void);
extern s32 lbl_803CA870[0x40];
s32 fn_801FD690(u8 *arg0) {
    if (fn_801F15A4(lbl_803CA870[0]) != 0) {
        arg0[4] = 0;
        return 2;
    }
    if (fn_80105194(fn_801059B0()) < 0) {
        arg0[4] = 1;
        return 2;
    }
    return 0;
}
