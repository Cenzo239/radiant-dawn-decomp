#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80045274(void *);
#else
s32 fn_80045274();
#endif
s32 fn_801A2224();
extern u8 lbl_803CA870[0x130];
extern u8 lbl_8041EB20[0x128];

s32 fn_8004B800(void) {
    if (fn_801A2224(lbl_8041EB20) != 0) {
        return 0x40;
    }
    if ((fn_80045274(lbl_803CA870) == 0) && ((s32) M2C_FIELD(lbl_803CA870, u8 *, 0x28) != 0)) {
        return 0x10;
    }
    return 9;
}
