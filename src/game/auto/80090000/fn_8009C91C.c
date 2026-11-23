#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_800180F0(void *);
#if TARGET_PC
FE10_PROTO void fn_8001A954(char *);
#else
M2C_UNK fn_8001A954();
#endif
M2C_UNK fn_8009C76C(void *);
#if TARGET_PC
FE10_PROTO void fn_80176A34(int);
FE10_PROTO void fn_8017DE4C(char *, float, float);
#else
M2C_UNK fn_80176A34();
M2C_UNK fn_8017DE4C();
#endif
extern f32 lbl_804CD230;
extern f32 lbl_804CD234;

void fn_8009C91C(s8 *arg0) {
    s8 *temp_r3;
    f32 a, b;

    fn_8009C76C(arg0);
    temp_r3 = M2C_FIELD(arg0, s8 **, 0x30);
    if ((temp_r3 != NULL) && ((s32) M2C_FIELD(temp_r3, s32 *, 0x44) != 0)) {
        fn_800180F0(temp_r3);
        fn_8001A954(M2C_FIELD(arg0, s8 **, 0x30));
        fn_80176A34(0x89);
        if (M2C_FIELD(arg0, u16 *, 0x38) & 2) {
            a = lbl_804CD230;
            b = lbl_804CD234;
            fn_8017DE4C(M2C_FIELD(arg0, s8 **, 0x30), a, b);
        }
    }
}

