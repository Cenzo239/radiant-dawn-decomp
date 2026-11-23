#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008939C(void *);
#else
M2C_UNK fn_8008939C();
#endif

void fn_801D2D80(s8 *arg0) {
    fn_8008939C(M2C_FIELD(arg0, s32 *, 0x50));
}
