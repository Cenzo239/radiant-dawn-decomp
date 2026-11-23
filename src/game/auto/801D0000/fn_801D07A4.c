#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
s8 *fn_801D07A4(u8 *p){ s32 v = -1; s8 c = *p; if (c >= 0) v = c; if (v < 0) return NULL; return (s8*)p + (v << 5) + 0x50; }
