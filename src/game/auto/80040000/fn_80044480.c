#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8012F5CC(void *, int);
#else
M2C_UNK fn_8012F5CC();
#endif
M2C_UNK fn_8012FCC0();
s8 * fn_8012FCD0();

struct A44480 { u8 pad[0x30]; s8 f30; s16 f32; };
void fn_80044480(struct A44480 *arg0) {
    s8 *temp_r3;

    fn_8012FCC0();
    temp_r3 = fn_8012FCD0();
    if (temp_r3 != NULL) {
        fn_8012F5CC(temp_r3, arg0->f30);
        M2C_FIELD(temp_r3, f32 *, 8) = (f32) arg0->f32;
    }
}

