#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8007A3BC(void *, void *);
#else
M2C_UNK fn_8007A3BC();
#endif

void fn_801060A4(s8 *arg0) {
    fn_8007A3BC(M2C_FIELD(arg0, s32 *, 0x54), arg0);
}
