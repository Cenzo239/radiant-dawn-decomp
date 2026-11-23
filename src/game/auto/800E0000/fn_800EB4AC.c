#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
f32 fn_800D5F6C(s32*);
#if TARGET_PC
FE10_PROTO void * fn_800D64B0(void *, int);
FE10_PROTO void * fn_800E3A10(char *, s8*);
FE10_PROTO void fn_800E49AC(void *, f32);
FE10_PROTO void fn_800E5BB0(void *, char *);
FE10_PROTO int fn_801CFA90(void *);
FE10_PROTO int fn_801CFDEC(void *, int);
#else
s32 fn_800D64B0();
s32 fn_800E3A10(s32, s8*);
void fn_800E49AC(s32, f32);
M2C_UNK fn_800E5BB0(s32, s32);
s32 fn_801CFA90();
s32 fn_801CFDEC();
#endif
s32 fn_801D0214(s8*, s32);
#if TARGET_PC
FE10_PROTO void * fn_801D0784(void *, int);
#else
s32 * fn_801D0784();
#endif

void fn_800EB4AC(s8 *arg0, s32 arg1) {
    s32 *temp_r31;
    s32 temp_r3;
    s32 t;

    temp_r31 = fn_801D0784(M2C_FIELD(arg0, s8 **, 0x30), fn_801D0214(M2C_FIELD(arg0, s8 **, 0x30), arg1));
    if (fn_801CFDEC(M2C_FIELD(arg0, s8 **, 0x30), arg1) != 0) {
        if ((s32) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u8 *, 0xB) != 1) {
            return;
        }
        goto block_5;
    }
    if ((fn_801CFA90(M2C_FIELD(arg0, s8 **, 0x30)) == 0) || ((s32) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u8 *, 0xB) == 1)) {
block_5:
        if ((temp_r31 != NULL) && ((t = fn_800D64B0(M2C_FIELD(arg0, s8 **, 0x30), arg1)) != 0)) {
            temp_r3 = fn_800E3A10(t, arg0);
            if (temp_r3 != 0) {
                fn_800E5BB0(temp_r3, *temp_r31);
                fn_800E49AC(temp_r3, fn_800D5F6C(temp_r31));
            }
        }
    }
}

