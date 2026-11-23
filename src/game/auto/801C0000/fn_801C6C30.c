#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO float fn_8017F68C(int, float, float, float, float, ...);
#else
M2C_UNK fn_80083B78();
f32 fn_8017F68C();
#endif
extern f32 lbl_804CF390;
extern f32 lbl_804CF470;
extern f32 lbl_804CF474;
extern f32 lbl_804CF520;
extern f32 lbl_804CF6C0;
extern f32 lbl_804CF6CC;

void fn_801C6C30(s8 *arg0) {
    f32 f0, f1;
    s16 temp_r4;
    s16 temp_r4_2;
    s8 *temp_r31;

    temp_r31 = M2C_FIELD(arg0, s8 **, 0x30);
    M2C_FIELD(temp_r31, s16 *, 8) = (s16) (M2C_FIELD(temp_r31, s16 *, 8) - 1);
    if ((s32) M2C_FIELD(temp_r31, s32 *, 0x10) == 1) {
        temp_r4 = M2C_FIELD(temp_r31, s16 *, 8);
        M2C_FIELD(temp_r31, f32 *, 0x1C) = fn_8017F68C(4, temp_r4, lbl_804CF520, lbl_804CF390, (f32) (7 - temp_r4), lbl_804CF6C0);
        M2C_FIELD(temp_r31, f32 *, 0x28) = (f32) lbl_804CF474;
    } else {
        temp_r4_2 = M2C_FIELD(temp_r31, s16 *, 8);
        M2C_FIELD(temp_r31, f32 *, 0x1C) = fn_8017F68C(4, temp_r4_2, lbl_804CF6CC, lbl_804CF390, (f32) (7 - temp_r4_2), lbl_804CF6C0);
        M2C_FIELD(temp_r31, f32 *, 0x28) = (f32) lbl_804CF474;
    }
    f1 = lbl_804CF390;
    f0 = lbl_804CF470;
    M2C_FIELD(temp_r31, f32 *, 0x18) = f1;
    M2C_FIELD(temp_r31, f32 *, 0x24) = f0;
    if ((s16) M2C_FIELD(temp_r31, s16 *, 8) <= 0) {
        fn_80083B78(arg0);
    }
}

