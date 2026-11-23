#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s32 fn_80058718();
#if TARGET_PC
FE10_PROTO int fn_8012A7B8(void *, int);
FE10_PROTO void fn_80186DAC(void *, void *);
FE10_PROTO void fn_80186DFC(void *, void *);
FE10_PROTO void fn_80186E9C(void *, void *);
#else
M2C_UNK fn_8012A7B8();
M2C_UNK fn_80186DAC();
M2C_UNK fn_80186DFC();
M2C_UNK fn_80186E9C();
#endif
s32 fn_801D3DEC();
extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CA870[0x130];

s32 fn_801C7068(s32 arg0) {
    s32 temp_r31;
    s32 a;

    temp_r31 = M2C_FIELD(lbl_803CA870, s32 *, 0);
    fn_8012A7B8(temp_r31, a = M2C_FIELD(lbl_803CA870, s8 *, 0xE));
    M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) = (s32) (M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) | 0x2000);
    if (fn_801D3DEC(lbl_803C8E80) != 0) {
        fn_80186DFC(temp_r31, arg0);
    } else if (fn_80058718() != 0) {
        fn_80186E9C(temp_r31, arg0);
    } else {
        fn_80186DAC(temp_r31, arg0);
    }
    return 0;
}

