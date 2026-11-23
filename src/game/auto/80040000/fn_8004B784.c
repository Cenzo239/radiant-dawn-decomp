#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(char *);
#else
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_804CA198[0x6];

void fn_8004B784(void) {
    fn_800D0864(lbl_804CA198);
}
