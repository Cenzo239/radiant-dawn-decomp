#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80291188(char *, char *);
#else
s32 fn_80291188();
#endif
extern s8 *lbl_804CB814;

s32 fn_8008DD3C(s32 arg0) {
    s32 *temp_r3;
    s32 var_r31;
    s8 *var_r30;

    var_r31 = 0;
    var_r30 = M2C_FIELD(lbl_804CB814, s8 **, 0xC);
    goto loop_3;
block_1:
    temp_r3 = M2C_FIELD(var_r30, s32 **, 0xEC);
    var_r30 = M2C_FIELD(var_r30, s8 **, 0xE8);
    if (fn_80291188(*temp_r3, arg0) != 0) {
        goto loop_3;
    }
    var_r31 += 1;
loop_3:
    if (var_r30 != NULL) {
        goto block_1;
    }
    return var_r31;
}
