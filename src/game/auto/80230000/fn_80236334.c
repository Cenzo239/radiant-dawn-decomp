#include "game/auto/m2c_prelude.h"
s32 OSDisableInterrupts();
M2C_UNK OSRestoreInterrupts();
#if TARGET_PC
FE10_PROTO void * fn_802BCD60(void *);
#else
M2C_UNK fn_802BCD60();
#endif
extern s32 lbl_804CBF50;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBF60;
#else
extern s32 lbl_804CBF60;
#endif

void fn_80236334(void) {
    s32 temp_r31;

    temp_r31 = OSDisableInterrupts();
    if ((s32) lbl_804CBF60 != 0) {
        fn_802BCD60(lbl_804CBF60);
    }
    OSRestoreInterrupts(temp_r31);
    lbl_804CBF50 = 0;
}
