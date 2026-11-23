#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8004A70C(char *);
#else
s32 fn_8004A70C();
#endif
extern u8 lbl_80379348[0x10];

s32 fn_80025EFC(void) {
    s32 temp_r3;

    temp_r3 = fn_8004A70C(lbl_80379348);
    return ((s32) (-temp_r3 | temp_r3) >> 0x1F) & 3;
}
