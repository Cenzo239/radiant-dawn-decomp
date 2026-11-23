#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8008A780(char *, int, void*);
#else
void fn_8008A780(int, int, void*);
#endif
extern u8 lbl_804CB8D0[0x4];
void fn_8017DA3C(int a) { fn_8008A780(a, 8, lbl_804CB8D0); }
