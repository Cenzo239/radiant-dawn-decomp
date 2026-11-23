#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_800D7D74(void);
FE10_PROTO int fn_80194524(void *);
#else
s32 fn_800D7D74();
M2C_UNK fn_80194524();
#endif

void fn_800496F8(s32 arg0) {
    if (fn_800D7D74() == 0) {
        fn_80194524(arg0);
    }
}
