#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
u64 OSGetTime();
extern s32 lbl_804CB710; extern u32 lbl_804CB714;
void fn_800CDF7C(void){ u64 t = OSGetTime(); lbl_804CB714 = (u32)t; lbl_804CB710 = (u32)(t>>32); }
