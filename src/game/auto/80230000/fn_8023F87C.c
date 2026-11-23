#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8023EF74();

#if TARGET_PC
s32 fn_8023F87C(void) {
    return fn_8023EF74();
}
#else
void fn_8023F87C(void) {
    fn_8023EF74();
}
#endif
