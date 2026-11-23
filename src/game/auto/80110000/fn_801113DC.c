#include "game/auto/m2c_prelude.h"
extern u8 lbl_803680E8[0x678];

s8 *fn_801113DC(s32 arg0) {
    if (arg0 >= 0x14B) {
        return lbl_803680E8 + 0x639;
    }
    if (arg0 >= 0xFB) {
        return lbl_803680E8 + 0x63E;
    }
    if (arg0 >= 0xB5) {
        return lbl_803680E8 + 0x640;
    }
    if (arg0 >= 0x79) {
        return lbl_803680E8 + 0x642;
    }
    if (arg0 >= 0x47) {
        return lbl_803680E8 + 0x644;
    }
    if (arg0 >= 0x1F) {
        return lbl_803680E8 + 0x646;
    }
    if (arg0 >= 1) {
        return lbl_803680E8 + 0x648;
    }
    return lbl_803680E8 + 0x64C;
}
