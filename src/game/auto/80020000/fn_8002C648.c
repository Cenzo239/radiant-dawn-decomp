#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80030D84(void *);
#else
s32 fn_80030D84();
#endif

s8 *fn_8002C648(s8 *arg0) {
    s32 temp_r4;
    s8 *var_r3;

    if (((s32) M2C_FIELD(arg0, s32 *, 0xEC) == 0) && ((s32) M2C_FIELD(arg0, s32 *, 0x58C) == 0)) {
        var_r3 = NULL;
    } else {
        temp_r4 = M2C_FIELD(arg0, s32 *, 0x15EC);
        if (temp_r4 & 0x100) {
            var_r3 = NULL;
        } else if (temp_r4 & 1) {
            if (fn_80030D84(arg0) != 0) {
                var_r3 = arg0;
            } else {
                var_r3 = NULL;
            }
        } else if (fn_80030D84(arg0 + 0x4A0) != 0) {
            var_r3 = arg0 + 0x4A0;
        } else if (fn_80030D84(arg0) != 0) {
            var_r3 = arg0;
        } else {
            var_r3 = NULL;
        }
    }
    if ((s32) var_r3 == 0) {
        return NULL;
    }
    if (var_r3 == arg0) {
        return arg0 + 0x4A0;
    }
    if (var_r3 == (s8 *) (arg0 + 0x4A0)) {
        return arg0;
    }
    return NULL;
}
