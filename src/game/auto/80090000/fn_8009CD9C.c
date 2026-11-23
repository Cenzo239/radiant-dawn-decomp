#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80083B84(void *);
#else
s8 * fn_80083B84();
#endif
extern u8 lbl_80381A18[0x24];
extern s32 lbl_804CB700;

s32 fn_8009CD9C(void) {
    s8 *temp_r3;

    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    temp_r3 = fn_80083B84(lbl_80381A18);
    if ((temp_r3 == NULL) || (M2C_FIELD(temp_r3, u16 *, 0x38) & 1)) {
        return 0;
    }
    return 1;
}
