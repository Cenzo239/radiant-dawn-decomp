#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern u8 lbl_80389FB8[0x14];
extern u8 lbl_80389FCC[0x13];
extern u8 lbl_80389FE0[0x12];
extern u8 lbl_80389FF4[0x13];
extern u8 lbl_8038A008[0x12];
extern u8 lbl_8038A01C[0x15];

M2C_UNK *fn_801BC5E0(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 1:
        return lbl_8038A01C;
    case 2:
        return lbl_8038A008;
    case 3:
        return lbl_80389FF4;
    case 4:
        return lbl_80389FE0;
    case 5:
        return lbl_80389FCC;
    default:
        return lbl_80389FB8;
    }
}

