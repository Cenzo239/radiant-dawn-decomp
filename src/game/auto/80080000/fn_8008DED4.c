#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80291188(char *, char *);
#else
s32 fn_80291188();
#endif
extern u8 lbl_803631E0[0x110];
extern s8 *lbl_804CB814;

s32 fn_8008DED4(void) {
    s32 *temp_r3;
    s32 var_r30;
    s8 *var_r29;

    var_r30 = 0;
    var_r29 = M2C_FIELD(lbl_804CB814, s8 **, 0xC);
    goto loop_3;
block_1:
    temp_r3 = M2C_FIELD(var_r29, s32 **, 0xF0);
    var_r29 = M2C_FIELD(var_r29, s8 **, 0xE8);
    if (fn_80291188(*temp_r3, lbl_803631E0 + 0x43) != 0) {
        goto loop_3;
    }
    var_r30 += 1;
loop_3:
    if (var_r29 != NULL) {
        goto block_1;
    }
    return var_r30;
}
