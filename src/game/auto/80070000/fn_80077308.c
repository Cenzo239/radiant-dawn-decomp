#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8031DE20(void *);
#else
M2C_UNK fn_8031DE20();
#endif

void fn_80077308(s32 arg0) {
    fn_8031DE20(arg0 + 4);
}
