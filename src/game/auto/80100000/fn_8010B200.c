#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
#else
M2C_UNK fn_80076F54(s32);
#endif

void
#if TARGET_PC
*
#endif
fn_8010B200(
#if TARGET_PC
const char *arg0
#else
s32 arg0
#endif
) {
#if TARGET_PC
    return fn_80076F54(arg0);
#else
    fn_80076F54(arg0);
#endif
}
