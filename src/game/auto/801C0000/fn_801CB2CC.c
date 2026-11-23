#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80008F20(void *, unsigned char);
FE10_PROTO void * fn_800811E4(void *, void *);
#else
M2C_UNK fn_80008F20();
s8 * fn_800811E4();
#endif
M2C_UNK fn_80081A90(void *);
#if TARGET_PC
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
s8 * fn_800893E4();
#endif
extern u8 fn_801CA674[0x14];
extern u8 lbl_8038AD88[0x20];

void fn_801CB2CC(
#if TARGET_PC
s8 *arg0, void *arg1, s32 arg2
#else
s8 *arg0, s32 arg1, s32 arg2
#endif
) {
    s8 *var_r3;

    if (arg2 == 0) {
        var_r3 = fn_800893E4(lbl_8038AD88, fn_801CA674, arg0);
        if (var_r3 != NULL) {
            fn_80081A90(var_r3);
        }
        fn_80008F20(arg0 + 0x14, 0);
        return;
    }
    if ((s32) M2C_FIELD(arg0, u8 *, 0x1F) != 0) {
        var_r3 = fn_800893E4(lbl_8038AD88, fn_801CA674, arg0);
        if (var_r3 != NULL) {
            if ((s32) M2C_FIELD(var_r3, u8 *, 0x3D) == 0) {
                return;
            }
            goto block_9;
        }
        var_r3 = fn_800811E4(lbl_8038AD88, arg1);
block_9:
        M2C_FIELD(var_r3, u8 *, 0x3C) = (u8) M2C_FIELD(arg0, u8 *, 0x1F);
        M2C_FIELD(var_r3, s8 *, 0x3D) = 0;
        M2C_FIELD(var_r3, s32 *, 0x34) = 0;
        M2C_FIELD(var_r3, s32 *, 0x38) = arg2;
        M2C_FIELD(var_r3, s8 **, 0x30) = arg0;
    }
}
