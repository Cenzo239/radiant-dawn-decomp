#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80030D84(void *);
#else
s32 fn_80030D84();
#endif

s8 *fn_8002C590(s8 *arg0) {
    s32 temp_r4;

    if (((s32) M2C_FIELD(arg0, s32 *, 0xEC) == 0) && ((s32) M2C_FIELD(arg0, s32 *, 0x58C) == 0)) {
        return NULL;
    }
    temp_r4 = M2C_FIELD(arg0, s32 *, 0x15EC);
    if (temp_r4 & 0x100) {
        return NULL;
    }
    if (temp_r4 & 1) {
        if (fn_80030D84(arg0) != 0) {
            return arg0;
        }
        return NULL;
    }
    if (fn_80030D84(arg0 + 0x4A0) != 0) {
        return arg0 + 0x4A0;
    }
    if (fn_80030D84(arg0) != 0) {
        return arg0;
    }
    return NULL;
}
