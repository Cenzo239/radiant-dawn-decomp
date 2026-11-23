#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(char *, int);
#else
M2C_UNK fn_8023F1A0();
#endif

void fn_8017DA54(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    fn_8023F1A0(arg0 + 0x30, M2C_FIELD(arg0, s32 *, 0x74));
}
