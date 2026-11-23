#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801288D4(void *);
#else
M2C_UNK fn_801288D4();
#endif
#if TARGET_PC
FE10_PROTO s32 fn_8012CA88(void *);
#else
s32 fn_8012CA88();
#endif
extern u8 lbl_803CA870[0x130];

void fn_80044DC4(void) {
#if TARGET_PC
    if ((M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 0), s32 *, 0x10C) & 0x800000) && (fn_8012CA88(M2C_FIELD(lbl_803CA870, s8 **, 0)) == 0)) {
        fn_801288D4(M2C_FIELD(lbl_803CA870, s8 **, 0));
    }
    if ((M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 4), s32 *, 0x10C) & 0x800000) && (fn_8012CA88(M2C_FIELD(lbl_803CA870, s8 **, 4)) == 0)) {
        fn_801288D4(M2C_FIELD(lbl_803CA870, s8 **, 4));
    }
#else
    if ((M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 0), s32 *, 0x10C) & 0x800000) && (fn_8012CA88() == 0)) {
        fn_801288D4(M2C_FIELD(lbl_803CA870, s8 **, 0));
    }
    if ((M2C_FIELD(M2C_FIELD(lbl_803CA870, s8 **, 4), s32 *, 0x10C) & 0x800000) && (fn_8012CA88() == 0)) {
        fn_801288D4(M2C_FIELD(lbl_803CA870, s8 **, 4));
    }
#endif
}
