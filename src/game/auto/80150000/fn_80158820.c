#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_801586C8(void *, void *, int *, int *, void *);
#else
s32 fn_801586C8();
#endif
extern u8 lbl_803C8E80[0x1648];
extern f32 lbl_804CE2DC;

s32 fn_80158820(s8 *arg0, s8 *arg1) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fn_801586C8(lbl_803C8E80, lbl_803C8E80 + 0x4A0, &spC, &sp8, 0);
    if (temp_r3 & 1) {
        var_r31 = -0x32;
    }
    if (temp_r3 & 2) {
        var_r31 += 0x32;
    }
    if (temp_r3 & 4) {
        var_r31 += spC;
    }
    if (temp_r3 & 8) {
        var_r31 -= sp8;
    }
    if (arg1 != NULL) {
        M2C_FIELD(arg1, u8 *, 0xC) = (u8) (M2C_FIELD(arg1, u8 *, 0xC) | temp_r3);
    }
    if (arg0 != NULL) {
        spC = (s32) (lbl_804CE2DC * ((f32) spC * (f32) (s8) M2C_FIELD(arg0, u8 *, 5)));
        sp8 = (s32) (lbl_804CE2DC * ((f32) sp8 * (f32) (s8) M2C_FIELD(arg0, u8 *, 0xB)));
    }
    return var_r31 + (spC - sp8);
}
