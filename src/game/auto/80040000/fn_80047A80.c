#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_80111A0C(void *, void *, void *);
#else
M2C_UNK fn_80111A0C();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80047A80(s32 arg0) {
    fn_80111A0C(M2C_FIELD(lbl_803CA870, s32 *, 0), M2C_FIELD((M2C_FIELD(lbl_803CA870, s32 *, 0) + ((s8) M2C_FIELD(lbl_803CA870, u8 *, 0xE) * 0x28)), s32 *, 0x1BC), arg0);
}

