#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO int fn_80291188(char *, char *);
#else
s32 fn_80291188();
#endif
extern u8 lbl_803680E8[0x678];

s32 fn_801112A8(s8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x639) == 0) {
        return 0x14B;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x63C) == 0) {
        return 0x14B;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x63E) == 0) {
        return 0xFB;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x640) == 0) {
        return 0xB5;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x642) == 0) {
        return 0x79;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x644) == 0) {
        return 0x47;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x646) == 0) {
        return 0x1F;
    }
    if (fn_80291188(arg0, lbl_803680E8 + 0x648) == 0) {
        return 1;
    }
    fn_80291188(arg0, lbl_803680E8 + 0x64A);
    return 0;
}

