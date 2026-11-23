#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8017D1DC(unsigned char *);
#else
M2C_UNK fn_8017D1DC(s32);
#endif

void fn_8017D7D8(s32 arg0) {
    fn_8017D1DC(arg0);
}
