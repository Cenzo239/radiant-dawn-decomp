#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8031DD44(void *);
#else
M2C_UNK fn_8031DD44();
#endif

void fn_80077340(s32 arg0) {
    fn_8031DD44(arg0 + 4);
}
