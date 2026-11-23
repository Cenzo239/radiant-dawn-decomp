#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_802358B8(void *);
#else
M2C_UNK fn_802358B8(s32);
#endif
s32 fn_80237C68();
#if TARGET_PC
FE10_PROTO void fn_80237CE4(int);
#else
M2C_UNK fn_80237CE4();
#endif

void fn_802357E4(void) {
    s32 temp_r31;

loop_1:
    temp_r31 = fn_80237C68();
    fn_802358B8(temp_r31);
    fn_80237CE4(temp_r31);
    goto loop_1;
}
