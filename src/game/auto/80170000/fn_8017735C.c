#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80081A90(void *);
#else
M2C_UNK fn_80081A90();
#endif

s32 fn_8017735C(s8 *arg0, u32 arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 0x30) == arg1) {
        fn_80081A90(M2C_FIELD(arg0, s32 *, 0x18));
    }
    return 0;
}
