#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80078E24(void *);
FE10_PROTO void fn_80079210(void *);
#else
M2C_UNK fn_80078E24();
M2C_UNK fn_80079210();
#endif

s8 *fn_8017AB5C(s8 *arg0, s32 arg1) {
    if (arg0 != NULL) {
        if (((arg0 + 0x24) != 0) && (((u32) M2C_FIELD(arg0, u32 *, 0x24) >> 0x1FU) != 0)) {
            fn_80079210(M2C_FIELD(arg0, s32 *, 0x2C));
        }
        if (((arg0 + 0x18) != NULL) && (((u32) M2C_FIELD(arg0, u32 *, 0x18) >> 0x1FU) != 0)) {
            fn_80079210(M2C_FIELD(arg0, s32 *, 0x20));
        }
        if (arg1 > 0) {
            fn_80078E24(arg0);
        }
    }
    return arg0;
}
