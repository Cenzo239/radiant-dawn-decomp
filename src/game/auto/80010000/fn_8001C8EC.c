#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8030585C();

#if TARGET_PC
u32 fn_8001C8EC(void) {
    return fn_8030585C(0x260, 0x1C0, 4, 0, 0);
}
#else
void fn_8001C8EC(void) {
    fn_8030585C(0x260, 0x1C0, 4, 0, 0);
}
#endif
