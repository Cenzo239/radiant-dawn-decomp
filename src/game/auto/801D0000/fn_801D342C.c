#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void fn_800893D4(void *);
FE10_PROTO void fn_801E5890(void *);
#else
M2C_UNK fn_80083B78();
M2C_UNK fn_800893D4();
M2C_UNK fn_801E5890();
#endif

void fn_801D342C(s8 *arg0) {
    fn_800893D4(M2C_FIELD(arg0, s32 *, 0x4C));
    fn_801E5890(arg0);
    fn_80083B78(arg0);
}
