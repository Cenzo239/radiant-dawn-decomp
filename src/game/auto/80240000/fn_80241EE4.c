#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80079210(void *); FE10_PROTO void fn_801E40B0(void *, int);
#else
void fn_80079210(s32); void fn_801E40B0(s32, int);
#endif
s32 fn_80241EE4(s32 a, s32 b){ if (a != 0) { fn_801E40B0(a, 0); if (b > 0) fn_80079210(a); } return a; }
