#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
FE10_PROTO char * fn_800D0864(char *);
#else
s32 fn_80076F54();
s32 fn_800D0864(s32);
#endif

s32
#if TARGET_PC
*
#endif
fn_8010F5E0(s8 *arg0) {
    if (fn_80076F54(M2C_FIELD(arg0, s32 *, 4)) != 0) {
        return fn_800D0864(M2C_FIELD(arg0, s32 *, 4));
    }
    return M2C_FIELD(arg0, s32 *, 0);
}
