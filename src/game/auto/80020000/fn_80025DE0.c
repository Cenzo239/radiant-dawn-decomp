#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
FE10_PROTO char * fn_800D0864(char *);
#else
s8 * fn_80060728();
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_803792D0[0x9];
extern u8 lbl_803792DC[0xb];
extern u8 lbl_803CAB38[0x988];

void fn_80025DE0(void) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11);
    if ((s32) temp_r0 == 2) {
        goto block_6;
    }
    if ((s32) temp_r0 >= 2) {
        goto block_4;
    }
    if ((s32) temp_r0 >= 0) {
        goto block_5;
    }
    goto block_6;
block_4:
    if ((s32) temp_r0 >= 4) {
        goto block_6;
    }
block_5:
    fn_800D0864(lbl_803792DC);
    return;
block_6:
    fn_800D0864(lbl_803792D0);
    return;
}
