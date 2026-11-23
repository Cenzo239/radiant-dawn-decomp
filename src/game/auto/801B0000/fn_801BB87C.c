#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern u8 lbl_80389D58[0x14]; extern u8 lbl_80389D6C[0x14]; extern u8 lbl_80389D80[0x14];
void *fn_801BB87C(int a, s32 b){ switch (b) { case 1: return lbl_80389D80; case 2: return lbl_80389D6C; default: return lbl_80389D58; } }
