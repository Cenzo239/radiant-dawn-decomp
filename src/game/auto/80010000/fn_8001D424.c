#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A2C(void **);
#else
M2C_UNK fn_80006A2C();
#endif

void fn_8001D424(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
#if TARGET_PC
    void *sp8;
#else
    s32 sp8;
#endif

    sp8 = arg0;
    fn_80006A2C(&sp8);
}
