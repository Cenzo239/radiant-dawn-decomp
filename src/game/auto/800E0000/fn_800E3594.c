#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80008F20(s8*, u8); void fn_8001A4DC(s8*); u8 fn_8007E03C();
void fn_800E3594(s8 *a){ u8 t = *(u8*)(a+0xB); u8 v = (u8)((t * fn_8007E03C())/255); if (v != 0) { fn_80008F20(a, v); fn_8001A4DC(a); fn_80008F20(a, t); } }
