#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_8002460C();
#if TARGET_PC
FE10_PROTO int fn_80060754(void *);
FE10_PROTO int fn_8010E2F4(void *);
#else
s32 fn_80060754();
s32 fn_8010E2F4();
#endif
extern u8 lbl_803CAB38[0x988];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB814;
#else
extern s32 lbl_804CB814;
#endif

s32 fn_801FC8BC(void) {
    s32 var_r31;

    var_r31 = 0;
    if (fn_8002460C() == 0) {
        var_r31 = fn_8010E2F4(lbl_804CB814);
    }
    var_r31 += fn_8010E2F4(lbl_804CB814 + 0x3C);
    if ((var_r31 <= 1) && (fn_80060754(lbl_803CAB38) == 0)) {
        return 2;
    }
    return 0;
}

