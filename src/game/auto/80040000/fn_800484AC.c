#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800E8608(void *, void*); extern u8 fn_8004844C[0x60];
#else
void fn_800E8608(int, void*); extern u8 fn_8004844C[0x60];
#endif
void fn_800484AC(int a){ fn_800E8608(a, fn_8004844C); }
