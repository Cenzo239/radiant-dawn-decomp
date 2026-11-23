#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E174(void *, unsigned short);
#else
M2C_UNK fn_8007E174();
#endif

void fn_801BCA94(void) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
}
