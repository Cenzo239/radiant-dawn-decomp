#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_801A7B20(void *);
FE10_PROTO void fn_801E5880(void *);
#else
M2C_UNK fn_801A7B20();
M2C_UNK fn_801E5880(s32);
#endif

void fn_80023FB8(s32 arg0) {
    fn_801E5880(arg0);
    fn_801A7B20(arg0);
}
