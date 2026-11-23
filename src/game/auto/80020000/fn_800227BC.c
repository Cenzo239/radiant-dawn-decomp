#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B58(int);
#else
M2C_UNK fn_80083B58();
#endif

void fn_800227BC(void) {
loop_1:
    fn_80083B58(9);
    goto loop_1;
}
