#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern u8 lbl_80389CE4[0x14];
extern u8 lbl_80389CF8[0x18];
extern u8 lbl_80389D10[0x16];
extern u8 lbl_80389D28[0x15];

M2C_UNK *fn_801BB2E0(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 1:
        return lbl_80389D28;
    case 2:
        return lbl_80389D10;
    case 3:
        return lbl_80389CF8;
    default:
        return lbl_80389CE4;
    }
}

