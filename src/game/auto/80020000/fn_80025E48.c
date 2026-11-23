#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8004A70C(char *);
FE10_PROTO void * fn_80060728(void *);
#else
s32 fn_8004A70C();
s8 * fn_80060728();
#endif
extern u8 lbl_80379324[0xc];
extern u8 lbl_803CAB38[0x988];

s32 fn_80025E48(void) {
    u8 temp_r4;

    if (fn_8004A70C(lbl_80379324) != 0) {
        return 3;
    }
    temp_r4 = M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11);
    return ((s32) ~((temp_r4 - 2) | (2 - temp_r4)) >> 0x1F) & 3;
}
