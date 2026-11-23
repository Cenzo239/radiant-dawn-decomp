#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800E5884(void *, void *, void *);
#else
void fn_800E5884(int, int, int);
#endif
void fn_800E5878(
#if TARGET_PC
void *a, void *b
#else
int a, int b
#endif
) { fn_800E5884(a, 0, b); }
