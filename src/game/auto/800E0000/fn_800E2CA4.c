#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
FE10_PROTO void fn_800E24F8(char *);
#else
M2C_UNK fn_80083DC4();
M2C_UNK fn_800E24F8();
#endif
s32 fn_8017FA1C();

void fn_800E2CA4(s8 *arg0) {
    s32 var_r3;
    s8 *temp_r3;
    s8 *temp_r3_2;

    M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s32 *, 0x14) = fn_8017FA1C();
    temp_r3 = M2C_FIELD(arg0, s8 **, 0x30);
    if (M2C_FIELD(temp_r3, s32 *, 0x18) & 0x8000) {
        temp_r3_2 = M2C_FIELD(temp_r3, s8 **, 0xC4);
        if (temp_r3_2 == NULL) {
            var_r3 = 0;
        } else {
            var_r3 = M2C_FIELD(temp_r3_2, s32 *, 4);
        }
        fn_800E24F8(var_r3);
        return;
    }
    fn_80083DC4(arg0, 0);
}
