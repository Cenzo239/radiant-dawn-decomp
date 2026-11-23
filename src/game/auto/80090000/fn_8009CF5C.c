#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(char *, int);
#else
M2C_UNK fn_8023F1A0();
#endif
extern u8 lbl_80364A70[0x98];

void fn_8009CF5C(void) {
    fn_8023F1A0(lbl_80364A70, 0xC00);
}
