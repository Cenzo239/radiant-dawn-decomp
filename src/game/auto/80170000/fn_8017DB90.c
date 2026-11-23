#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800620A8(void *, float, float);
FE10_PROTO void * fn_80081194(void *, void *);
#else
M2C_UNK fn_800620A8();
s8 * fn_80081194();
#endif
extern u8 lbl_80387BD0[0x18];
extern u8 lbl_803CAB38[0x988];

void fn_8017DB90(
#if TARGET_PC
s32 arg0, s32 arg1, s8 arg2, s32 arg3, void *arg4
#else
s32 arg0, s32 arg1, s8 arg2, s32 arg3, s32 arg4
#endif
) {
    s8 *temp_r3;

    fn_800620A8(lbl_803CAB38, (f32) arg0, (f32) arg1);
    temp_r3 = fn_80081194(lbl_80387BD0, arg4);
    M2C_FIELD(temp_r3, s32 *, 0x30) = arg3;
    M2C_FIELD(temp_r3, s8 *, 0x34) = arg2;
}
