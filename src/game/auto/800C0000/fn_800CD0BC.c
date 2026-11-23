#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_801D09F0(void);
#else
s32 fn_801D09F0();
#endif
extern f32 lbl_804CD678;
extern f32 lbl_804CD67C;

s32 fn_800CD0BC(void) {
    f32 var_f0;

    if (fn_801D09F0() != 0) {
        var_f0 = lbl_804CD678;
    } else {
        var_f0 = lbl_804CD67C;
    }
    return (s32) var_f0;
}
