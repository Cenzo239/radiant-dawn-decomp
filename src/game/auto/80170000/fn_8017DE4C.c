#include "game/auto/m2c_prelude.h"
s8 * fn_80007F10(void *);
#if TARGET_PC
FE10_PROTO void fn_8017DC24(float, float, float, int, int);
#else
M2C_UNK fn_8017DC24();
#endif

void fn_8017DE4C(s8 *arg0, f32 farg0, f32 farg1) {
    s8 *temp_r3;

    if (arg0 != NULL) {
        temp_r3 = fn_80007F10(arg0);
        if (temp_r3 != NULL) {
            fn_8017DC24(M2C_FIELD(temp_r3, s32 *, 0x14), M2C_FIELD(temp_r3, s32 *, 0x18), farg0, farg1, M2C_FIELD(arg0, f32 *, 0x58));
        }
    }
}
