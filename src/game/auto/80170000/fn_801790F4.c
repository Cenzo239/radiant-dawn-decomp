#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO s32 fn_80007630(void *, char *);
FE10_PROTO void * fn_80081050(void *, void *);
FE10_PROTO void fn_8017794C(void *, void *, char *, char *);
#else
s32 fn_80007630(s32, s32);
s32 fn_80081050();
M2C_UNK fn_8017794C();
#endif
extern u8 lbl_80387AC8[0x38];

s32
#if TARGET_PC
*
#endif
fn_801790F4(
#if TARGET_PC
void *arg0, s8 *arg1, s8 *arg2, void *arg3
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3
#endif
) {
#if TARGET_PC
    void *temp_r31;
#else
    s32 temp_r31;
#endif

    if (fn_80007630(arg0, arg1) >= 0) {
        fn_80007630(arg0, arg2);
    }
    temp_r31 = fn_80081050(lbl_80387AC8, arg3);
    fn_8017794C(temp_r31, arg0, arg1, arg2);
    return temp_r31;
}

