#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8013CB90(int, int, void *);
#else
M2C_UNK fn_8013CB90();
#endif

void fn_80046F3C(s8 *arg0) {
    fn_8013CB90((s32) M2C_FIELD(arg0, f32 *, 0x30), (s32) M2C_FIELD(arg0, f32 *, 0x34), arg0);
}
