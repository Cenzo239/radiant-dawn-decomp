#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO s8 * fn_8010B228(char *);
FE10_PROTO void fn_80110D38(void *);
#else
s8 * fn_8010B228();
M2C_UNK fn_80110D38();
#endif

s32 fn_80110BFC(
#if TARGET_PC
s8 *arg0, const char *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s8 *temp_r3;

    temp_r3 = fn_8010B228(arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    fn_80110D38(arg0);
    M2C_FIELD(arg0, s8 **, 0) = temp_r3;
    M2C_FIELD(arg0, u8 *, 4) = (u8) M2C_FIELD(temp_r3, u8 *, 0x1B);
    return 1;
}
