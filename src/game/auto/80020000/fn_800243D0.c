#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801E5880(void *);
#else
M2C_UNK fn_801E5880(s32);
#endif

void fn_800243D0(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    fn_801E5880(arg0);
}
