#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *, ...);
FE10_PROTO void fn_8009E554(void *, void *);
#else
s32 fn_80076F54();
M2C_UNK fn_8009E554();
#endif

s32 fn_80089814(s8 *arg0) {
    s32 temp_r31;
    s8 *temp_r4;

    temp_r4 = M2C_FIELD(arg0, s8 **, 4);
    temp_r31 = M2C_FIELD(temp_r4, s32 *, 4);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r4 + 8);
    if (fn_80076F54(temp_r31, temp_r4) == 0) {
        return 1;
    }
    fn_8009E554(temp_r31, arg0);
    return 0;
}
