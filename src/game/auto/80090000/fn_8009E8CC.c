#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800C3BC8(void *);
#else
s32 fn_800C3BC8();
#endif

void fn_8009E8CC(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = fn_800C3BC8(0);
}
