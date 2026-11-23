#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
#else
M2C_UNK fn_80083DC4();
#endif
M2C_UNK fn_801E5890(s8 *);

void fn_800243F4(s8 *arg0) {
    fn_801E5890(arg0);
    fn_80083DC4(arg0, M2C_FIELD(arg0, u8 *, 0x54));
}
