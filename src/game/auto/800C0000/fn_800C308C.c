#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E174(void *, unsigned short);
FE10_PROTO void fn_8007E374(void *, void *, unsigned short);
FE10_PROTO void fn_8007E4E4(float, float, float, float);
FE10_PROTO void fn_8007E720(float);
FE10_PROTO void fn_8007E7DC(unsigned char);
FE10_PROTO void fn_800800D4(unsigned int);
#else
M2C_UNK fn_8007E174();
M2C_UNK fn_8007E374();
M2C_UNK fn_8007E4E4();
M2C_UNK fn_8007E720();
M2C_UNK fn_8007E7DC();
M2C_UNK fn_800800D4();
#endif
M2C_UNK fn_80080308();
#if TARGET_PC
FE10_PROTO void fn_80080430(float, float, float, float, float, float);
#else
M2C_UNK fn_80080430();
#endif
M2C_UNK fn_80080494();
#if TARGET_PC
FE10_PROTO void fn_80080578(int);
FE10_PROTO int fn_800CB0FC(float, int);
FE10_PROTO void fn_80176EA8(int, int, int, char *);
#else
M2C_UNK fn_80080578();
s32 fn_800CB0FC();
M2C_UNK fn_80176EA8();
#endif
extern u8 lbl_80365D94[0xc];
extern f32 lbl_804CD4B8;
extern f32 lbl_804CD4F0;
extern f32 lbl_804CD4FC;
extern f32 lbl_804CD520;
extern f32 lbl_804CD548;

void fn_800C308C(s8 *arg0) {
    s32 temp_r31_2;
    u8 temp_r31;

    temp_r31 = M2C_FIELD(arg0, u8 *, 0x38);
    fn_8007E154();
    fn_8007E4E4((f32) M2C_FIELD(arg0, s16 *, 0x30), (f32) M2C_FIELD(arg0, s16 *, 0x32), (f32) M2C_FIELD(arg0, s16 *, 0x34), lbl_804CD4F0);
    fn_8007E374(M2C_FIELD(arg0, s32 *, 0x40), temp_r31 + 1, 0x11);
    fn_8007E7DC(M2C_FIELD(arg0, u8 *, 0x36));
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(lbl_804CD4B8, lbl_804CD4B8, lbl_804CD4B8, lbl_804CD4B8, lbl_804CD4FC, lbl_804CD548);
    if ((u8) M2C_FIELD(arg0, u8 *, 0x37) == 1) {
        fn_80080494();
    }
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(lbl_804CD520);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    temp_r31_2 = fn_800CB0FC(-1, lbl_804CD4F0) >> 1;
    fn_800800D4(5);
    if ((s32) M2C_FIELD(arg0, s32 *, 0x3C) != 0) {
        fn_80176EA8(0x64, 0x16 - temp_r31_2, 2, M2C_FIELD(arg0, s32 *, 0x3C));
    } else {
        fn_80176EA8(0x64, 0x16 - temp_r31_2, 2, lbl_80365D94 + 3);
    }
    fn_80080308();
}

