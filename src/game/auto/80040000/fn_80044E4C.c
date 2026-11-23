#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800D724C(void *);
FE10_PROTO unsigned char fn_800D7D74(void);
#else
M2C_UNK fn_800D724C();
s32 fn_800D7D74();
#endif

void fn_80044E4C(s32 arg0) {
    if (fn_800D7D74() == 0) {
        fn_800D724C(arg0);
    }
}
