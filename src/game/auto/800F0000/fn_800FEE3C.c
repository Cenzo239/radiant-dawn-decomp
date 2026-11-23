#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO float fn_8001EF30(float, float, float, float, ...);
#else
f32 fn_8001EF30();
#endif
M2C_UNK fn_80083B78(void *);
#if TARGET_PC
FE10_PROTO void fn_800F3F08(void *, int);
#else
M2C_UNK fn_800F3F08();
#endif

void fn_800FEE3C(s8 *arg0) {
    u16 temp_r3;
    u32 temp_r4;
    u16 temp_r6;

    temp_r6 = M2C_FIELD(arg0, u16 *, 0x34);
    temp_r4 = M2C_FIELD(arg0, u16 *, 0x38) + 1;
    M2C_FIELD(arg0, u16 *, 0x38) = temp_r4;
    if ((u16) temp_r4 >= temp_r6) {
        M2C_FIELD(arg0, u16 *, 0x38) = temp_r6;
        fn_80083B78(arg0);
    }
    temp_r3 = M2C_FIELD(arg0, u16 *, 0x34);
    fn_800F3F08(M2C_FIELD(arg0, s32 *, 0x30), (s32) fn_8001EF30(temp_r3, (f32) M2C_FIELD(arg0, u8 *, 0x50), (f32) M2C_FIELD(arg0, u8 *, 0x51), (f32) temp_r3, (f32) M2C_FIELD(arg0, u16 *, 0x38)));
}

