#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80330018();
extern u8 lbl_804CB0F8;

void fn_8002274C(void) {
    goto loop_2;
block_1:
    fn_80330018();
loop_2:
    if ((s32) lbl_804CB0F8 == 0) {
        goto block_1;
    }
    return;
}
