#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80011838(int);
#else
M2C_UNK fn_80011838();
#endif

s32 fn_80018684(s32 *arg0) {
    if (!(*arg0 & 0xE00273C0)) {
        return 0;
    }
    fn_80011838(-1);
    return 1;
}
