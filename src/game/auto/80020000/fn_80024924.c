#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(char *);
#else
M2C_UNK fn_800D0864();
#endif
extern u8 lbl_80378E68[0xd];

void fn_80024924(void) {
    fn_800D0864(lbl_80378E68);
}
