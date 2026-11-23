#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800CD4A4(int);
#else
M2C_UNK fn_800CD4A4();
#endif

void fn_800449FC(void) {
    fn_800CD4A4(0x13);
}
