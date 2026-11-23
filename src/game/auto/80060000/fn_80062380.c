#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_80068DF0();
u8 fn_80092E10(s8 *);
#if TARGET_PC
FE10_PROTO void * fn_8010B094(int);
FE10_PROTO void fn_8011337C(void *);
FE10_PROTO void fn_80114D00(void *);
#else
s8 * fn_8010B094();
M2C_UNK fn_8011337C();
M2C_UNK fn_80114D00();
#endif
M2C_UNK fn_80139A7C();
#if TARGET_PC
FE10_PROTO void * fn_8013B920(unsigned char);
FE10_PROTO void * fn_8013B9A8(void);
#else
s8 * fn_8013B920();
s32 fn_8013B9A8();
#endif
M2C_UNK strcpy();
extern u8 lbl_803EC898[0x15867];

void fn_80062380(
#if TARGET_PC
s8 *arg0, s8 *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
#if TARGET_PC
    s8 *var_r30;
#else
    s32 var_r30;
#endif
    u8 temp_r3;
    s8 *temp_r31;

    var_r30 = arg1;
    if (fn_8013B9A8() == 0) {
        if (var_r30 == 0) {
            var_r30 = M2C_FIELD(fn_8010B094(M2C_FIELD(arg0, u8 *, 0x10)), s32 *, 8);
        }
        if (var_r30 == 0) {
            M2C_FIELD(arg0, s8 *, 0x914) = 0;
        } else {
            strcpy(arg0 + 0x914, var_r30);
        }
        temp_r31 = fn_8013B920(0);
        fn_80139A7C(temp_r31, var_r30, 0);
        temp_r3 = M2C_FIELD(temp_r31, u8 *, 0x4E);
        if ((s8) temp_r3 != -1) {
            M2C_FIELD(arg0, u8 *, 0x92) = temp_r3;
        } else {
            M2C_FIELD(arg0, u8 *, 0x92) = fn_80092E10(fn_8010B094(M2C_FIELD(arg0, u8 *, 0x10)));
        }
        fn_8011337C(lbl_803EC898);
        fn_80114D00(lbl_803EC898);
        fn_80068DF0();
    }
}

