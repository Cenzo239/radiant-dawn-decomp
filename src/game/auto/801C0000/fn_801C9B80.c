#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8003D234(void *);
FE10_PROTO void fn_800482F8(char *, unsigned char *);
#else
M2C_UNK fn_8003D234();
M2C_UNK fn_800482F8();
#endif
extern u8 lbl_803CA870[0x130];

void fn_801C9B80(s32 arg0) {
    s8 sp8;

    sp8 = 0x43;
    fn_800482F8(lbl_803CA870, &sp8);
    fn_8003D234(arg0);
}
