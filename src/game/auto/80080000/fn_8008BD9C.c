#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80330018();
extern s32 lbl_804CB5F4;

void fn_8008BD9C(void) {
    goto loop_2;
block_1:
    fn_80330018();
loop_2:
    if (lbl_804CB5F4 & 0x01000000) {
        goto block_1;
    }
    return;
}
