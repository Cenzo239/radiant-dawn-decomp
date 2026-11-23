#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8004A70C(char *);
#else
s32 fn_8004A70C();
#endif
extern u8 lbl_803792AC[0xc];

s32 fn_80025B68(void) {
    s32 temp_r3;

    temp_r3 = fn_8004A70C(lbl_803792AC);
    return ((s32) (-temp_r3 | temp_r3) >> 0x1F) & 3;
}
