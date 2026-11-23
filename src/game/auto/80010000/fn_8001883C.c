#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80011838(int);
#else
M2C_UNK fn_80011838();
#endif

s32 fn_8001883C(s8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    if (!(M2C_FIELD(arg0, u16 *, 4) & 0xE038)) {
        return 0;
    }
    fn_80011838(-1);
    return 1;
}
