#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8000FF74(void *);
FE10_PROTO void fn_800104DC(void *);
FE10_PROTO void fn_801762B4(int, int, int, int);
#else
M2C_UNK fn_8000FF74();
M2C_UNK fn_800104DC();
M2C_UNK fn_801762B4();
#endif

void fn_801769F4(void) {
    fn_8000FF74(0);
    fn_801762B4(0, 0, 0x260, 0x1C0);
    fn_800104DC(0);
}
