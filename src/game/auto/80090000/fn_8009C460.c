#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80272404(void *);
#else
M2C_UNK fn_80272404(s32);
#endif

void fn_8009C460(s32 arg0) {
    fn_80272404(arg0);
}
