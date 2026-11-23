#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s8 * fn_80083B84();
#endif
s8 * fn_8024BCA0();
extern u8 lbl_803832E0[0x680];
extern s8 *lbl_804CBFD0;

void fn_800CD580(void) {
    s8 *temp_r31;
    s8 *temp_r31_2;

    temp_r31 = lbl_804CBFD0;
    M2C_FIELD(temp_r31, s8 *, 0x36) = (s8) M2C_FIELD(fn_80083B84(lbl_803832E0), s32 *, 0x64);
    M2C_FIELD(temp_r31, s8 *, 0x37) = 0xA;
    temp_r31_2 = fn_8024BCA0();
    M2C_FIELD(temp_r31_2, s8 *, 0x36) = (s8) M2C_FIELD(fn_80083B84(lbl_803832E0), s32 *, 0x64);
    M2C_FIELD(temp_r31_2, s8 *, 0x37) = 0xA;
}
