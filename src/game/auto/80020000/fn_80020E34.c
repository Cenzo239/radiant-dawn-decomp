#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80079978(void *);
#else
M2C_UNK fn_80079978();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB0A8;
#else
extern s32 lbl_804CB0A8;
#endif
extern s32 lbl_804CB0AC;
extern s32 lbl_804CB0B0;

void fn_80020E34(void) {
    s32 temp_r0;

    temp_r0 = lbl_804CB0AC - 1;
    lbl_804CB0AC = temp_r0;
    if (temp_r0 == 0) {
        fn_80079978(lbl_804CB0A8);
        lbl_804CB0A8 = 0;
        lbl_804CB0B0 = 0;
    }
}
