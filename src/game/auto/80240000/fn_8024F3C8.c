#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s8 * fn_80076F54(char *);
#else
s8 * fn_80076F54(s32);
#endif

s16 fn_8024F3C8(
#if TARGET_PC
s8 *arg0
#else
s32 arg0
#endif
) {
    s8 *temp_r3;

    temp_r3 = fn_80076F54(arg0);
    if (temp_r3 != NULL) {
        return M2C_FIELD(temp_r3, s16 *, 0x22);
    }
    return -1;
}
