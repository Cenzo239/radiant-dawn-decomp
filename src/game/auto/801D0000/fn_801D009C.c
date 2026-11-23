#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO char * fn_800D0864(u8*);
FE10_PROTO char * fn_8011A054(void *);
FE10_PROTO void * fn_801CFF0C(void *, s32);
#else
s32 fn_800D0864(u8*);
s32 fn_8011A054(s32);
s32 fn_801CFF0C(s32, s32);
#endif
extern u8 lbl_8036EA40[0x20];

s32
#if TARGET_PC
*
#endif
fn_801D009C(
#if TARGET_PC
void *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
#if TARGET_PC
    void *temp_r3;
#else
    s32 temp_r3;
#endif

    switch (arg1) {                                 /* irregular */
    case 0x6F:
        return fn_800D0864(lbl_8036EA40);
    case 0x6D:
        return fn_800D0864(lbl_8036EA40 + 8);
    case 0x7E:
        return fn_800D0864(lbl_8036EA40 + 0x18);
    default:
        temp_r3 = fn_801CFF0C(arg0, arg1);
        if (temp_r3 != 0) {
            return fn_8011A054(temp_r3);
        }
        return 0;
    }
}

