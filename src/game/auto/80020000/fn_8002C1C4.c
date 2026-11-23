#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8002600C(void *, unsigned int, short);
#else
M2C_UNK fn_8002600C();
#endif
M2C_UNK fn_8006D19C();
#if TARGET_PC
FE10_PROTO unsigned char fn_801204E8(void *);
FE10_PROTO u8 fn_801207B4(void *, s32);
FE10_PROTO unsigned char fn_80126B0C(void *);
#else
u8 fn_801204E8();
u8 fn_801207B4(s32, s32);
u8 fn_80126B0C();
#endif

void fn_8002C1C4(s32 arg0, s32 arg1) {
    u8 var_r31;

    var_r31 = fn_801207B4(arg0, arg1);
    if (var_r31 > fn_801204E8(arg0)) {
        var_r31 = fn_801204E8(arg0);
    }
    if (var_r31 != 0) {
        fn_8002600C(arg0 + 0xDE0, 0x2B, 0U);
        fn_8002600C(arg0 + 0xDE0, 0x2D, fn_80126B0C(arg0));
        fn_8002600C(arg0 + 0xDE0, 0x2E, var_r31);
        fn_8006D19C(arg0, var_r31, arg0 + 0xDE0);
    }
}
