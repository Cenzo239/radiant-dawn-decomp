#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
#else
s32 fn_80076F54(s32);
#endif
#if TARGET_PC
FE10_PROTO char * fn_80291480(char *, char *);
#else
s8 * fn_80291480();
#endif
extern u8 lbl_80368054[0x84];

s32 fn_8010DAC4(
#if TARGET_PC
s8 *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
    s8 *temp_r3;

    if (fn_80076F54(arg0) == 0) {
        return 0;
    }
    temp_r3 = fn_80291480(arg0, lbl_80368054 + 0x39);
    if (temp_r3 == NULL) {
        return 0;
    }
    return (s8) M2C_FIELD(temp_r3, u8 *, 5) == (arg1 + 0x30);
}
