#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_800E5884(void *, void *, void *);
#else
void fn_800E5884(int, s32, s32);
#endif
void fn_800E5BC0(
#if TARGET_PC
void *a, s8 *p, s8 *q
#else
int a, s8 *p, s8 *q
#endif
){ fn_800E5884(a, *(s32*)(p+0x3F0), *(s32*)(q+0x3F0)); }
