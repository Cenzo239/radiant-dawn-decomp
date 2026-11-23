#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800761F0(void *);
#else
M2C_UNK fn_800761F0();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB704;
FE10_PROTO extern void *lbl_804CB708;
#else
extern s32 lbl_804CB704;
extern s32 lbl_804CB708;
#endif

void fn_800CDB4C(void) {
    if ((s32) lbl_804CB704 != 0) {
        fn_800761F0(lbl_804CB704);
        lbl_804CB704 = 0;
    }
    if ((s32) lbl_804CB708 != 0) {
        fn_800761F0(lbl_804CB708);
        lbl_804CB708 = 0;
    }
}

