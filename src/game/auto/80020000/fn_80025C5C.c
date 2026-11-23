#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(char *);
#else
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_804CA078[0x8];

void fn_80025C5C(void) {
    fn_800D0864(lbl_804CA078);
}
