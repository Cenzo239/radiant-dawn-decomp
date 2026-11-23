#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80079940(int, int);
FE10_PROTO void fn_800C3584(void *);
#else
s32 fn_80079940();
M2C_UNK fn_800C3584();
#endif

s32 fn_801D0B20(s8 *arg0, s32 arg1) {
    s32 temp_r3;

    fn_800C3584(0);
    temp_r3 = fn_80079940(arg1 * 4, 0x40);
    M2C_FIELD(arg0, s32 *, 0) = temp_r3;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    if (temp_r3 == 0) {
        fn_800C3584(4);
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 0x18) = temp_r3;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    return 1;
}
