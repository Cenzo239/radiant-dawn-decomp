#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
#else
void fn_80083DC4(int, int);
#endif

void fn_801780B0(
#if TARGET_PC
void *a
#else
int a
#endif
) {
    fn_80083DC4(a, 0x63);
}
