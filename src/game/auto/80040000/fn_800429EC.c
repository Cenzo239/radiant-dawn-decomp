#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO unsigned char * fn_80044FD0(char *);
#else
M2C_UNK fn_80044FD0();
#endif
extern u8 lbl_803CA870[0x130];

void fn_800429EC(void) {
    fn_80044FD0(lbl_803CA870);
}
