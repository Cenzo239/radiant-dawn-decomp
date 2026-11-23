#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80291188(char *, char *);
#else
s32 fn_80291188();
#endif
extern u8 lbl_803631E0[0x110];
extern s8 *lbl_804CB814;

s32 fn_8008DDB0(void) {
    s32 *temp_r3;
    s32 temp_r30;
    s32 var_r29;
    s8 *var_r28;

    var_r29 = 0;
    var_r28 = M2C_FIELD(lbl_804CB814, s8 **, 0xC);
    goto loop_5;
block_1:
    temp_r3 = M2C_FIELD(var_r28, s32 **, 0xF0);
    var_r28 = M2C_FIELD(var_r28, s8 **, 0xE8);
    temp_r30 = *temp_r3;
    if (fn_80291188(temp_r30, lbl_803631E0 + 0xD) == 0) {
        goto block_4;
    }
    if (fn_80291188(temp_r30, lbl_803631E0 + 0x18) == 0) {
        goto block_4;
    }
    if (fn_80291188(temp_r30, lbl_803631E0 + 0x23) != 0) {
        goto loop_5;
    }
block_4:
    var_r29 += 1;
loop_5:
    if (var_r28 != NULL) {
        goto block_1;
    }
    return var_r29;
}
