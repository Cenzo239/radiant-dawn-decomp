#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *, ...);
FE10_PROTO void fn_80083DC4(void *, int);
#else
s32 fn_80076F54();
M2C_UNK fn_80083DC4();
#endif

s32 fn_800897AC(s8 *arg0) {
    u32 temp_r4;
    s32 v;
    s16 h;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 4);
    temp_r4 = (u32) M2C_FIELD(temp_r5, u32 *, 0) >> 0x10U;
    v = M2C_FIELD(temp_r5, s32 *, 4);
    M2C_FIELD(arg0, s8 **, 4) = (s8 *) (temp_r5 + 8);
    h = (s16) temp_r4;
    if (fn_80076F54(v, temp_r4, temp_r5) == 0) {
        fn_80083DC4(arg0, (u8) h);
    }
    return 1;
}

