#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char fn_80022698(void);
#else
s32 fn_80022698();
#endif
s32 fn_8031F6BC();
extern u8 lbl_8042A470[0x4328];

s32 fn_80246510(void) {
    s32 temp_r3;
    s32 var_r31;

    var_r31 = 1;
    temp_r3 = fn_8031F6BC(lbl_8042A470);
    if ((((u32) (-temp_r3 | temp_r3) >> 0x1FU) == 0) && (fn_80022698() == 0)) {
        var_r31 = 0;
    }
    return var_r31;
}
