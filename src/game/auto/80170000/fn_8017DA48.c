#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8008A43C(char *, int, void*); extern u8 lbl_804CB8D0[0x4];
#else
void fn_8008A43C(int, int, void*); extern u8 lbl_804CB8D0[0x4];
#endif
void fn_8017DA48(int a){ fn_8008A43C(a, 8, lbl_804CB8D0); }
