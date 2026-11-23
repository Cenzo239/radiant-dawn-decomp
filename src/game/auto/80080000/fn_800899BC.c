#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
extern s8 lbl_803CAB38[0x988];
s32 fn_800899BC(s8 *a) { u32 **pp = (u32**)(a+4); u32 v = **pp >> 16; lbl_803CAB38[0x9C] = v; *pp = *pp + 1; return 1; }
