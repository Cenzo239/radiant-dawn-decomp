#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8003D234(void *);
FE10_PROTO unsigned char * fn_80044FD0(char *);
FE10_PROTO void fn_800453B4(char *, char);
FE10_PROTO void fn_800482F8(char *, unsigned char *);
FE10_PROTO void fn_8010F4F0(unsigned char *, void *);
#else
M2C_UNK fn_8003D234();
s32 * fn_80044FD0();
M2C_UNK fn_800453B4();
M2C_UNK fn_800482F8();
M2C_UNK fn_8010F4F0();
#endif
extern u8 lbl_803CA870[0x130];

void fn_801C7A04(s32 arg0) {
    M2C_UNK sp8;

    fn_800453B4(lbl_803CA870, 0xA);
    fn_8010F4F0(&sp8, *fn_80044FD0(lbl_803CA870));
    fn_800482F8(lbl_803CA870, &sp8);
    fn_8003D234(arg0);
}
