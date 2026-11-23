#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80010788(int, unsigned char, void *, void *);
#else
M2C_UNK fn_80010788();
#endif
extern u8 fn_8017751C[0x430];

void fn_80178C98(s8 *arg0) {
    M2C_UNK var_r3;

    var_r3 = 3;
    if (M2C_FIELD(arg0, u8 *, 0x50) & 8) {
        var_r3 = 4;
    }
    fn_80010788(var_r3, 0x97, fn_8017751C, arg0);
}
