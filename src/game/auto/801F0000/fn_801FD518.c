#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO s32 fn_80105158(void *);
FE10_PROTO void * fn_801059B0(void);
FE10_PROTO int fn_8012ABFC(void *);
#else
s32 fn_80105158(s32);
s32 fn_801059B0(void);
s32 fn_8012ABFC();
#endif
struct S870 { s32 a; u8 pad[0x12c]; };
extern struct S870 lbl_803CA870;

s32 fn_801FD518(s8 *arg0) {
    s32 temp_r31;

    temp_r31 = lbl_803CA870.a;
    if (fn_80105158(fn_801059B0()) == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 0;
        return 2;
    }
    if (fn_8012ABFC(temp_r31) != 0) {
        M2C_FIELD(arg0, s8 *, 4) = 1;
        return 2;
    }
    return 0;
}

