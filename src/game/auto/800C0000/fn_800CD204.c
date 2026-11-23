#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8017F990(int, int);
#else
s32 fn_8017F990();
#endif
f64 fn_80295940();
extern u8 lbl_80383158[0x118];
extern f32 lbl_804CD688;
extern f32 lbl_804CD68C;
extern f32 lbl_804CD690;
extern f32 lbl_804CD694;
extern f32 lbl_804CD698;
extern f32 lbl_804CD69C;
extern f32 lbl_804CD6A0;
extern f32 lbl_804CD6A4;
extern f32 lbl_804CD6A8;
extern f32 lbl_804CD6AC;
extern f32 lbl_804CD6B0;
extern f32 lbl_804CD6B4;
extern f32 lbl_804CD6B8;
extern f32 lbl_804CD6BC;
extern f32 lbl_804CD6C0;

s8 *fn_800CD204(s32 arg0) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f4;
    f32 temp_f5;
    s8 *temp_r31;

    temp_r31 = lbl_80383158 + ((arg0 * 4) & 0x3FC);
    switch (arg0) {                                 /* irregular */
    case 0x27:
    case 0x13:
        temp_f2 = (f32) fn_8017F990(0, 0x5DC);
        temp_f3 = (lbl_804CD690 * (f32) fn_80295940(lbl_804CD68C * (temp_f2 / lbl_804CD688), temp_f2)) + lbl_804CD690;
        temp_f1 = (lbl_804CD698 * temp_f3) + lbl_804CD694;
        M2C_FIELD(temp_r31, s8 *, 0) = (s8) temp_f1;
        M2C_FIELD(temp_r31, s8 *, 1) = (s8) ((lbl_804CD698 * temp_f3) + lbl_804CD69C);
        M2C_FIELD(temp_r31, s8 *, 2) = (s8) temp_f1;
        break;
    case 0x14:
        temp_f2_2 = (f32) fn_8017F990(0, 0x5DC);
        temp_f3_2 = (lbl_804CD690 * (f32) fn_80295940(lbl_804CD68C * (temp_f2_2 / lbl_804CD688), temp_f2_2)) + lbl_804CD690;
        temp_f1_2 = (lbl_804CD6A0 * temp_f3_2) + lbl_804CD694;
        M2C_FIELD(temp_r31, s8 *, 0) = (s8) temp_f1_2;
        M2C_FIELD(temp_r31, s8 *, 1) = (s8) ((lbl_804CD6A0 * temp_f3_2) + lbl_804CD6A4);
        M2C_FIELD(temp_r31, s8 *, 2) = (s8) temp_f1_2;
        break;
    case 0x36:
        temp_f2_3 = (f32) fn_8017F990(0, 0x5DC);
        temp_f5 = (lbl_804CD690 * (f32) fn_80295940(lbl_804CD68C * (temp_f2_3 / lbl_804CD688), temp_f2_3)) + lbl_804CD690;
        M2C_FIELD(temp_r31, s8 *, 0) = (s8) ((lbl_804CD6AC * temp_f5) + lbl_804CD6A8);
        M2C_FIELD(temp_r31, s8 *, 1) = (s8) ((lbl_804CD6B4 * temp_f5) + lbl_804CD6B0);
        M2C_FIELD(temp_r31, s8 *, 2) = (s8) ((lbl_804CD6BC * temp_f5) + lbl_804CD6B8);
        break;
    case 0x40:
        temp_f2_4 = (f32) fn_8017F990(0, 0x5DC);
        temp_f4 = (lbl_804CD690 * (f32) fn_80295940(lbl_804CD68C * (temp_f2_4 / lbl_804CD688), temp_f2_4)) + lbl_804CD690;
        temp_f2_5 = (lbl_804CD6A4 * temp_f4) + lbl_804CD6C0;
        M2C_FIELD(temp_r31, s8 *, 0) = 0;
        M2C_FIELD(temp_r31, s8 *, 1) = (s8) temp_f2_5;
        M2C_FIELD(temp_r31, s8 *, 2) = (s8) ((lbl_804CD6BC * temp_f4) + lbl_804CD6B8);
        break;
    }
    return temp_r31;
}
