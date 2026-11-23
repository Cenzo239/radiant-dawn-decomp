#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8010DF10(char *, char);
FE10_PROTO void fn_8010E168(void *, void *);
FE10_PROTO void fn_8010E27C(void *, void *);
#else
M2C_UNK fn_8010DF10();
M2C_UNK fn_8010E168();
M2C_UNK fn_8010E27C();
#endif
extern s8 *lbl_804CB814;

void fn_800231E4(void) {
    s8 *sp8;
    s8 *temp_r31;
    s8 *temp_r31_2;
    s8 *temp_r31_3;
    s8 *var_r30;
    s8 *var_r30_2;
    s8 *var_r30_3;

    fn_8010DF10(&sp8, 5);
    var_r30 = M2C_FIELD(lbl_804CB814, s8 **, 0x3C);
    goto loop_4;
block_1:
    temp_r31 = M2C_FIELD(var_r30, s8 **, 0xE8);
    if (!(M2C_FIELD(var_r30, s32 *, 0x10C) & 0x400000)) {
        goto block_3;
    }
    fn_8010E27C(M2C_FIELD(var_r30, s32 *, 0xF4), var_r30);
    fn_8010E168(&sp8, var_r30);
block_3:
    var_r30 = temp_r31;
loop_4:
    if (var_r30 != NULL) {
        goto block_1;
    }
    var_r30_2 = M2C_FIELD(lbl_804CB814, s8 **, 0x3C);
    goto loop_8;
block_6:
    temp_r31_2 = M2C_FIELD(var_r30_2, s8 **, 0xE8);
    if (M2C_FIELD(var_r30_2, s32 *, 0x10C) & 0x400000) {
        goto block_9;
    }
    fn_8010E27C(M2C_FIELD(var_r30_2, s32 *, 0xF4), var_r30_2);
    fn_8010E168(&sp8, var_r30_2);
    var_r30_2 = temp_r31_2;
loop_8:
    if (var_r30_2 != NULL) {
        goto block_6;
    }
block_9:
    var_r30_3 = sp8;
    goto loop_11;
block_10:
    temp_r31_3 = M2C_FIELD(var_r30_3, s8 **, 0xE8);
    fn_8010E27C(M2C_FIELD(var_r30_3, s32 *, 0xF4), var_r30_3);
    fn_8010E168(lbl_804CB814 + 0x3C, var_r30_3);
    var_r30_3 = temp_r31_3;
loop_11:
    if (var_r30_3 != NULL) {
        goto block_10;
    }
    return;
}
