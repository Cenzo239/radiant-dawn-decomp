#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
FE10_PROTO void fn_80083DC4(void *, int);
#else
s8 * fn_80083B84();
M2C_UNK fn_80083DC4();
#endif
extern u8 lbl_8038B160[0x508];

s32 fn_801D411C(s32 arg0, s32 arg1, s8 *arg2) {
    s8 *t;
    if ((u8) M2C_FIELD(arg2, u8 *, 0x39) == 2) {
        return 0x10;
    }
    t = fn_80083B84(lbl_8038B160);
    M2C_FIELD(t, s32 *, 0x50) = arg1;
    fn_80083DC4(t, 0x15);
    return 4;
}

