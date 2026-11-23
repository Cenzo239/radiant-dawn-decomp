#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
#else
M2C_UNK fn_80083B78();
#endif
M2C_UNK fn_80185720();
#if TARGET_PC
FE10_PROTO void fn_801E5890(void *);
#else
M2C_UNK fn_801E5890(s32);
#endif

void fn_80024058(s32 arg0) {
    fn_801E5890(arg0);
    fn_80185720();
    fn_80083B78(arg0);
}
