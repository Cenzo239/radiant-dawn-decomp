#include "game/auto/m2c_prelude.h"
s32 fn_800626E0(void *);
#if TARGET_PC
FE10_PROTO void * fn_8010B094(int);
#else
s8 * fn_8010B094();
#endif
extern f32 lbl_804CCF20;

void fn_800615DC(s8 *arg0, s32 arg1) {
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r31;
    u8 temp_r0;

    var_r31 = arg1;
    temp_r3 = fn_800626E0(arg0);
    temp_r4 = var_r31 - temp_r3;
    if (temp_r4 < 0) {
        M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (M2C_FIELD(arg0, s32 *, 0xB4) + (temp_r3 - var_r31));
    } else {
        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) + temp_r4);
    }
    temp_r0 = M2C_FIELD(fn_8010B094(M2C_FIELD(arg0, u8 *, 0x10)), u8 *, 0x89);
    switch ((s32) temp_r0) {                        /* irregular */
    case 0:
        temp_r0_2 = (0x98967F - M2C_FIELD(arg0, s32 *, 0x1C)) - M2C_FIELD(arg0, s32 *, 0x20);
        if (var_r31 > temp_r0_2) {
            var_r31 = temp_r0_2;
        }
        if ((f32) var_r31 < lbl_804CCF20) {
            var_r31 = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x18) = var_r31;
        return;
    case 1:
        temp_r0_3 = (0x98967F - M2C_FIELD(arg0, s32 *, 0x18)) - M2C_FIELD(arg0, s32 *, 0x20);
        if (var_r31 > temp_r0_3) {
            var_r31 = temp_r0_3;
        }
        if ((f32) var_r31 < lbl_804CCF20) {
            var_r31 = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x1C) = var_r31;
        return;
    case 2:
        temp_r0_4 = (0x98967F - M2C_FIELD(arg0, s32 *, 0x18)) - M2C_FIELD(arg0, s32 *, 0x1C);
        if (var_r31 > temp_r0_4) {
            var_r31 = temp_r0_4;
        }
        if ((f32) var_r31 < lbl_804CCF20) {
            var_r31 = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x20) = var_r31;
        return;
    case 3:
        temp_r0_5 = 0x98967F - M2C_FIELD(arg0, s32 *, 0x18);
        if (var_r31 > temp_r0_5) {
            var_r31 = temp_r0_5;
        }
        if ((f32) var_r31 < lbl_804CCF20) {
            var_r31 = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x20) = var_r31;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        return;
    case 4:
        if (var_r31 > 0x98967F) {
            var_r31 = 0x98967F;
        }
        if ((f32) var_r31 < lbl_804CCF20) {
            var_r31 = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x20) = var_r31;
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        return;
    }
}
