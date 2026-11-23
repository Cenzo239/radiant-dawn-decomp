#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80031C38(void *, void *, ...);
FE10_PROTO unsigned char * fn_80044FD0(char *);
FE10_PROTO void fn_80128374(void *, int, int);
FE10_PROTO int fn_8012A7B8(void *, int);
#else
M2C_UNK fn_80031C38();
s8 ** fn_80044FD0();
M2C_UNK fn_80128374();
M2C_UNK fn_8012A7B8();
#endif
extern u8 lbl_803C8E80[0x1648];
struct S870 { s32 a; u8 pad[10]; s8 b; u8 pad2[0x121]; };
extern struct S870 lbl_803CA870;

s32 fn_801C74B4(s32 arg0) {
    s32 temp_r30;
    s8 *temp_r29;

    temp_r30 = lbl_803CA870.a;
    temp_r29 = *fn_80044FD0(&lbl_803CA870);
    fn_80128374(temp_r30, (s8) M2C_FIELD(temp_r29, u8 *, 0x2B), (s8) M2C_FIELD(temp_r29, u8 *, 0x2A));
    fn_8012A7B8(temp_r30, lbl_803CA870.b);
    M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) = (s32) (M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) | 0x2000);
    fn_80031C38(temp_r29, arg0, lbl_803C8E80);
    return 1;
}

