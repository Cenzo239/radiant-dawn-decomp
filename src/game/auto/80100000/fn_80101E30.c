#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
#else
void fn_80083DC4(int, int);
#endif

void fn_80101E30(int a) {
    fn_80083DC4(a, 2);
}
