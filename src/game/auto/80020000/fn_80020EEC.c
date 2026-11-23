#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80011CBC(void (*)(void *), void *);
#else
M2C_UNK fn_80011CBC();
#endif
extern u8 fn_80020E34[0x40];

void fn_80020EEC(void) {
    fn_80011CBC(fn_80020E34, 0);
}
