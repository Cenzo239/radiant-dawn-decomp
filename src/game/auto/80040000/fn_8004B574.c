#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80069CE4(void *, void *, int);
#else
void fn_80069CE4(int, int, int);
#endif

void fn_8004B574(int a, int b) {
    fn_80069CE4(a, b, 0);
}
