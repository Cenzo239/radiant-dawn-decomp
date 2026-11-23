#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern u8 lbl_80389E48[0x14];
extern u8 lbl_80389E5C[0x13];
extern u8 lbl_80389E70[0x13];
extern u8 lbl_80389E84[0x12];
extern u8 lbl_80389E98[0x15];

M2C_UNK *fn_801BBE68(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 1:
        return lbl_80389E98;
    case 2:
        return lbl_80389E84;
    case 3:
        return lbl_80389E70;
    case 4:
        return lbl_80389E5C;
    default:
        return lbl_80389E48;
    }
}

