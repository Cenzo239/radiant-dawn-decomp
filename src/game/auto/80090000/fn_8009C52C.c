#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800E3810(char *, void *, ...);
#else
s8 * fn_800E3810();
#endif
extern u8 lbl_80364968[0x48];

void fn_8009C52C(s32 arg0) {
    s8 *temp_r3;
    s8 *temp_r3_2;

    temp_r3 = fn_800E3810(lbl_80364968 + 0xC, arg0, lbl_80364968);
    if (temp_r3 != NULL) {
        temp_r3_2 = M2C_FIELD(temp_r3, s8 **, 0x30);
        M2C_FIELD(temp_r3_2, s32 *, 0x18) = (s32) (M2C_FIELD(temp_r3_2, s32 *, 0x18) | 4);
    }
}
