#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80102928(void *, int, int, unsigned short, void *);
#else
M2C_UNK fn_80102928();
#endif

void fn_80100EF8(s8 *arg0) {
    fn_80102928(M2C_FIELD(arg0, s32 *, 0x30), -1, 0x10, 0, arg0);
    M2C_FIELD(arg0, s8 *, 0x54) = 1;
}
