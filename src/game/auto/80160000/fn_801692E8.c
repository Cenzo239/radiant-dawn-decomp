#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800466B4(void *, void *);
#else
M2C_UNK fn_800466B4();
#endif
M2C_UNK fn_80171188(s8 *);
extern u8 lbl_803CA870[0x130];

void fn_801692E8(s32 arg0) {
    fn_800466B4(lbl_803CA870, arg0);
    if (((s8 *) M2C_FIELD(lbl_803CA870, s8 **, 0) != NULL) && ((s32) M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 0), s32 *, 0xEC) != 0)) {
        fn_80171188(M2C_FIELD(lbl_803CA870, s8 **, 0));
    }
    if (((s8 *) M2C_FIELD(lbl_803CA870, s8 **, 4) != NULL) && ((s32) M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 4), s32 *, 0xEC) != 0)) {
        fn_80171188(M2C_FIELD(lbl_803CA870, s8 **, 4));
    }
}
