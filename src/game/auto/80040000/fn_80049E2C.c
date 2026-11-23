#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_801038D0(void *, void *);
#else
M2C_UNK fn_801038D0();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80049E2C(s32 arg0) {
    fn_801038D0(M2C_FIELD(lbl_803CA870, s32 *, 0), arg0);
}

