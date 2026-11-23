#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8001A218(int, char *);
#else
M2C_UNK fn_8001A218();
#endif

void fn_8001A4DC(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    fn_8001A218(-1, arg0);
}
