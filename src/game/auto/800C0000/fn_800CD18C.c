#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_801D09F0(void);
#else
s32 fn_801D09F0();
#endif
extern f32 lbl_804CD680;
extern f32 lbl_804CD684;

s32 fn_800CD18C(void) {
    f32 var_f0;

    if (fn_801D09F0() != 0) {
        var_f0 = lbl_804CD680;
    } else {
        var_f0 = lbl_804CD684;
    }
    return (s32) var_f0;
}
