#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
FE10_PROTO void fn_800C3584(void *);
#else
s32 fn_80076F54();
M2C_UNK fn_800C3584();
#endif

s32 fn_801D0E68(
#if TARGET_PC
void *arg0, s8 *arg1
#else
s32 arg0, s32 arg1
#endif
) {
#if TARGET_PC
    void *temp_r3;
#else
    s32 temp_r3;
#endif

    fn_800C3584(0);
    temp_r3 = fn_80076F54(arg1);
    if (temp_r3 == 0) {
        fn_800C3584(5);
    }
    return temp_r3 != 0;
}

