#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_80291110(char *, char *);
#else
M2C_UNK fn_80291110();
#endif
M2C_UNK strcpy();
extern u8 lbl_80418640[0x40];

M2C_UNK *fn_8017F37C(
#if TARGET_PC
s8 *arg0, s8 *arg1, s8 *arg2
#else
s32 arg0, s32 arg1, s32 arg2
#endif
) {
    strcpy(lbl_80418640, arg0);
    fn_80291110(lbl_80418640, arg1);
    if (arg2 != 0) {
        fn_80291110(lbl_80418640, arg2);
    }
    return lbl_80418640;
}
