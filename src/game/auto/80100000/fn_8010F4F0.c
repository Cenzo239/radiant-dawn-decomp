#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8010B228(char *);
#else
u32 fn_8010B228();
#endif
extern u8 lbl_803680E8[0x678];

void fn_8010F4F0(
#if TARGET_PC
u8 *arg0, void *arg1
#else
u8 *arg0, u32 arg1
#endif
) {
    *arg0 = 0;
    if (arg1 == fn_8010B228(lbl_803680E8)) {
        *arg0 |= 1;
        return;
    }
    if (arg1 == fn_8010B228(lbl_803680E8 + 0x10)) {
        *arg0 |= 2;
        return;
    }
    if (arg1 == fn_8010B228(lbl_803680E8 + 0x1C)) {
        *arg0 |= 0x80;
    }
}
