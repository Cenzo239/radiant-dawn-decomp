#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E374(void *, void *, unsigned short);
FE10_PROTO void fn_8007E4E4(float, float, float, float);
#else
M2C_UNK fn_8007E374();
M2C_UNK fn_8007E4E4();
#endif
M2C_UNK fn_8007E7B4();
#if TARGET_PC
FE10_PROTO void fn_8007E7DC(unsigned char);
FE10_PROTO void fn_800800D4(unsigned int);
#else
M2C_UNK fn_8007E7DC();
M2C_UNK fn_800800D4();
#endif
M2C_UNK fn_80080308();
#if TARGET_PC
FE10_PROTO void fn_80080430(float, float, float, float, float, float, ...);
FE10_PROTO void fn_80080578(int);
#else
M2C_UNK fn_80080430();
M2C_UNK fn_80080578();
#endif
extern f32 lbl_804CF2C4;
extern f32 lbl_804CF2C8;
extern f32 lbl_804CF2CC;
extern f32 lbl_804CF340;
extern f32 lbl_804CF344;

void fn_801B6DD0(s8 *arg0, s32 arg1, f32 farg0, f32 farg1) {
    s32 temp_r3;

    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_8007E154();
    fn_8007E4E4(farg0, farg1, lbl_804CF2C4, lbl_804CF2C8);
    fn_8007E374(arg1, 2, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    temp_r3 = M2C_FIELD(arg0, u8 *, 0x22) * 0x24;
    fn_80080430(temp_r3, lbl_804CF2CC, lbl_804CF2CC, lbl_804CF2CC, (f32) temp_r3, lbl_804CF340, lbl_804CF344);
    fn_80080578(1);
    fn_80080308();
}
