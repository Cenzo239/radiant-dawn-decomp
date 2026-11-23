#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8001D424(void *);
FE10_PROTO void fn_80078E24(void *);
FE10_PROTO void fn_80081A90(void *);
#else
M2C_UNK fn_8001D424();
M2C_UNK fn_80078E24();
M2C_UNK fn_80081A90();
#endif

s8 *fn_801795E8(s8 *arg0, s32 arg1) {
    if (arg0 != NULL) {
        if ((s32) M2C_FIELD(arg0, s32 *, 0x34) != 0) {
            fn_8001D424(M2C_FIELD(arg0, s32 *, 0x34));
        }
        if ((s32) M2C_FIELD(arg0, s32 *, 0x30) != 0) {
            fn_80081A90(M2C_FIELD(arg0, s32 *, 0x30));
            M2C_FIELD(arg0, s32 *, 0x30) = 0;
        }
        if (arg1 > 0) {
            fn_80078E24(arg0);
        }
    }
    return arg0;
}

