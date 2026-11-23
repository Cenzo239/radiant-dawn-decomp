#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8009F3F0(void *);
FE10_PROTO unsigned char fn_800D7D74(void);
#else
M2C_UNK fn_8009F3F0();
s32 fn_800D7D74();
#endif

void fn_800497D8(s32 arg0) {
    if (fn_800D7D74() == 0) {
        fn_8009F3F0(arg0);
    }
}
