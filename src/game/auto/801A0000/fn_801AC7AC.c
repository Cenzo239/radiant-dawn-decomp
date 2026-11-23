#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E374(void *, void *, unsigned short);
FE10_PROTO void fn_8007E4E4(float, float, float, float);
#else
M2C_UNK fn_8007E374();
M2C_UNK fn_8007E4E4();
#endif
M2C_UNK fn_8007E7F4();
#if TARGET_PC
FE10_PROTO void fn_800800D4(unsigned int);
#else
M2C_UNK fn_800800D4();
#endif
M2C_UNK fn_80080308();
#if TARGET_PC
FE10_PROTO void fn_80080430(float, float, float, float, float, float);
FE10_PROTO void fn_80080578(int);
#else
M2C_UNK fn_80080430();
M2C_UNK fn_80080578();
#endif
extern f32 lbl_804CF000;
extern f32 lbl_804CF004;
extern f32 lbl_804CF020;
extern f32 lbl_804CF03C;
extern f32 lbl_804CF040;

void fn_8007E7DC(u8);
void fn_801AC7AC(
#if TARGET_PC
void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1
#else
s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1
#endif
) {
    s16 var_r31;

    fn_8007E154();
    fn_8007E4E4(farg0, farg1, lbl_804CF020, lbl_804CF000);
    fn_8007E374(arg0, 1, 0x11);
    fn_8007E7DC(arg2);
    fn_8007E164();
    var_r31 = 0x80 - (arg1 * 8);
    if (var_r31 > 0xE0) {
        var_r31 = 0xE0;
    }
    if (var_r31 < 0) {
        var_r31 = 0;
    }
    fn_800800D4(1);
    fn_80080430((f32) -var_r31, lbl_804CF004, lbl_804CF004, lbl_804CF004, lbl_804CF03C, lbl_804CF040);
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}

