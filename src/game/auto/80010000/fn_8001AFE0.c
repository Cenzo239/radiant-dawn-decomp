#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8* fn_80007F3C(void*); void fn_80010788(int, int, void*, void*); s32 fn_80014DE4(s8*, int);
extern u8 fn_8001AEEC[0xf4];
void fn_8001AFE0(s8 *a){ if (*(u8*)(a+0xB) != 0) { if (fn_80014DE4(fn_80007F3C(a), 0x400) != 0) fn_80010788(4, *(u8*)(a+0x82), fn_8001AEEC, a); } }
