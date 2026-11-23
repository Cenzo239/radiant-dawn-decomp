#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800893C4(void *);
FE10_PROTO void fn_801E5880(void *);
FE10_PROTO void * fn_80216744(int);
#else
M2C_UNK fn_800893C4();
M2C_UNK fn_801E5880();
M2C_UNK fn_80216744();
#endif

void fn_801D3330(s8 *arg0) {
    fn_800893C4(M2C_FIELD(arg0, s32 *, 0x4C));
    fn_801E5880(arg0);
    fn_80216744(arg0);
}
