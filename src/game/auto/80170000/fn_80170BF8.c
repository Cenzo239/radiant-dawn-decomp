#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s8 * fn_8012CE54(void *);
#else
s8 * fn_8012CE54(s32);
#endif

s32 fn_80170BF8(s32 arg0) {
    s32 temp_r3;
    s8 *temp_r3_2;

    temp_r3_2 = fn_8012CE54(arg0);
    if (temp_r3_2 == NULL) {
        return 0;
    }
    temp_r3 = M2C_FIELD(temp_r3_2, s32 *, 0x10C);
    if (temp_r3 & 4) {
        return 1;
    }
    return (temp_r3 & 0x98) == 0;
}
