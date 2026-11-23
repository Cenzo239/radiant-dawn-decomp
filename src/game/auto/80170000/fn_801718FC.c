#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8010B228(char *);
#else
u32 fn_8010B228();
#endif
extern u8 lbl_8036B2DC[0x2c];

s32 fn_801718FC(
#if TARGET_PC
void *arg0
#else
u32 arg0
#endif
) {
    s32 var_r30;

    var_r30 = 0;
    if (arg0 == fn_8010B228(lbl_8036B2DC)) {
        var_r30 = 1;
    } else if (arg0 == fn_8010B228(lbl_8036B2DC + 0x10)) {
        var_r30 = 2;
    } else if (arg0 == fn_8010B228(lbl_8036B2DC + 0x1C)) {
        var_r30 = 0x80;
    }
    return var_r30;
}
