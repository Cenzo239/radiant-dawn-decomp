#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800893AC(void *);
#else
M2C_UNK fn_800893AC();
#endif

void fn_801D2C54(s8 *arg0) {
    fn_800893AC(M2C_FIELD(arg0, s32 *, 0x50));
}
