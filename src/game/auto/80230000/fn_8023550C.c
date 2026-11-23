#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_80303624();
M2C_UNK fn_803061BC();
M2C_UNK fn_80308054();
#if TARGET_PC
FE10_PROTO void fn_80308090(float, float, float, float, float, float, ...);
#else
M2C_UNK fn_80308090();
#endif
s32 fn_80331194();
s32 fn_8033119C();
M2C_UNK fn_8033119C();
extern s32 lbl_804CB5F0;
extern s8 *lbl_804CBF28;
extern f32 lbl_804CFF68;
extern f32 lbl_804CFF6C;

void fn_8023550C(void) {
    u16 temp_r3;
    s32 t;
    u16 temp_r4;
    s8 *temp_r31;

    lbl_804CB5F0 = fn_80331194();
    temp_r31 = lbl_804CBF28;
    if ((s32) M2C_FIELD(temp_r31, u8 *, 0x18) != 0) {
        t = fn_8033119C();
        temp_r4 = M2C_FIELD(temp_r31, u16 *, 4);
        fn_80308054(t, lbl_804CFF68, lbl_804CFF68, (f32) temp_r4, (f32) M2C_FIELD(temp_r31, u16 *, 6), lbl_804CFF68, lbl_804CFF6C);
    } else {
        temp_r3 = M2C_FIELD(temp_r31, u16 *, 4);
        fn_80308090(temp_r3, lbl_804CFF68, lbl_804CFF68, (f32) temp_r3, (f32) M2C_FIELD(temp_r31, u16 *, 6), lbl_804CFF68, lbl_804CFF6C);
    }
    fn_80303624();
    fn_803061BC();
}

