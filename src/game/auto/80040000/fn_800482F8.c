#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8010F598(unsigned char *);
#else
M2C_UNK fn_8010F598();
#endif

void fn_800482F8(s8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, u8 *, 0x17) = (u8) *arg1;
    fn_8010F598(arg0 + 0x17);
}
