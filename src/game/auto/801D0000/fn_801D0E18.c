#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_801D0EC0(s8 *);
s32 fn_801D0E18(s8 *a){ s32 *t; if (*(s32*)(a+0xC) == 0) return 0; fn_801D0EC0(a); t = *(s32**)(a+0x18) - 1; *(s32**)(a+0x18) = t; return *t; }
