#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
#else
s8 * fn_80076F54();
#endif
s32 fn_8016D090();
#if TARGET_PC
FE10_PROTO unsigned int fn_8016D0B0(void *);
#else
s32 fn_8016D0B0();
#endif

s32 fn_8016335C(s8 *arg0) {
    if ((fn_8016D090() != 0) || (fn_8016D0B0(arg0) != 0)) {
        return 1;
    }
    return M2C_FIELD(fn_80076F54(M2C_FIELD(arg0, s32 *, 0x3A0)), u8 *, 7) != 0;
}
