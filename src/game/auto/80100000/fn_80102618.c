#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800FBDF0(void *);
#else
M2C_UNK fn_800FBDF0();
#endif

void fn_80102618(s8 *arg0) {
    fn_800FBDF0(M2C_FIELD(arg0, s32 *, 0x30));
}
