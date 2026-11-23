#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern u8 lbl_80389DA0[0x14];
extern u8 lbl_80389DB4[0x16];
extern u8 lbl_80389DCC[0x15];
extern u8 lbl_80389DE4[0x14];
extern u8 lbl_80389DF8[0x15];
extern u8 lbl_80389E10[0x17];
extern u8 lbl_80389E28[0x14];

M2C_UNK *fn_801BBB1C(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 1:
        return lbl_80389E28;
    case 2:
        return lbl_80389E10;
    case 3:
        return lbl_80389DF8;
    case 4:
        return lbl_80389DE4;
    case 5:
        return lbl_80389DCC;
    case 6:
        return lbl_80389DB4;
    default:
        return lbl_80389DA0;
    }
}

