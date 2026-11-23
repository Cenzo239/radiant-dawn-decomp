#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
#else
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
#else
extern s32 lbl_804CA4E8;
#endif

s32 fn_801C7750(s8 *arg0) {
    s8 *temp_r3;
    s32 t;

    if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E8) == 0) {
        return 0;
    }
    if ((s8) M2C_FIELD(arg0, u8 *, 0xFE) < 0x1E) {
        return 0;
    }
    temp_r3 = M2C_FIELD(arg0, s8 **, 0xF0);
    if ((temp_r3 == NULL) || ((t = M2C_FIELD(temp_r3, s32 *, 0xB4)) == 0)) {
        return 0;
    }
    return fn_8011B77C(arg0 + 0x12C, t) == 0;
}

