#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8012FCB0();
s8 * fn_8012FCD0();

void fn_8004442C(s8 *arg0) {
    s8 *temp_r3;

    fn_8012FCB0();
    temp_r3 = fn_8012FCD0();
    if (temp_r3 != NULL) {
        M2C_FIELD(arg0, s8 *, 0x30) = (s8) M2C_FIELD(temp_r3, s32 *, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) M2C_FIELD(temp_r3, f32 *, 8);
    }
}
