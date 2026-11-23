#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800391E0(void *, ...);
#else
void fn_800391E0(int, int);
#endif
int fn_800A2A20(
#if TARGET_PC
void *a
#else
int a
#endif
) { fn_800391E0(a, 0); return 1; }
