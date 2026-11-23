#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80306EFC(s32, u32); extern u32 lbl_803BFA18[16]; extern s8 lbl_804CB0E9;
void fn_80021FF0(s32 a, u32 b){ if (b != lbl_803BFA18[a]) { fn_80306EFC(a, b); lbl_803BFA18[a] = b; lbl_804CB0E9 = 1; } }
