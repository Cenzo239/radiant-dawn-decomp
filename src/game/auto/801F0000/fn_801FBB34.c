#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801288D4(void *);
FE10_PROTO int fn_8012CA88(void *);
#else
M2C_UNK fn_801288D4();
s32 fn_8012CA88();
#endif
extern u8 lbl_803CA870[0x130];

void fn_801FBB34(void) {
    s8 *temp_r31;
    s8 *temp_r30;

    temp_r30 = M2C_FIELD(lbl_803CA870, s8 **, 0);
    temp_r31 = M2C_FIELD(lbl_803CA870, s8 **, 4);
    if ((temp_r30 != NULL) && (M2C_FIELD(temp_r30, s32 *, 0x10C) & 0x800000) && (fn_8012CA88(temp_r30) == 0)) {
        fn_801288D4(temp_r30);
    }
    if ((temp_r31 != NULL) && (M2C_FIELD(temp_r31, s32 *, 0x10C) & 0x800000) && (fn_8012CA88(temp_r31) == 0)) {
        fn_801288D4(temp_r31);
    }
}
