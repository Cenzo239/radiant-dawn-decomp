#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8012CBF0();
s8 * fn_8024BCA0();

void fn_80043D3C(void) {
    s8 *temp_r3;

    temp_r3 = fn_8024BCA0();
    M2C_FIELD(temp_r3, s32 *, 0x40) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x40) & 0xFFFFFFC7);
    fn_8012CBF0();
}
