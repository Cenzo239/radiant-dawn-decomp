#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(char *, int);
#else
void fn_8023F1A0(int, int);
#endif
void fn_8024CF4C(int a) { fn_8023F1A0(a, 0x880); }
