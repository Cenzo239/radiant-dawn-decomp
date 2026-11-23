#include "game/auto/m2c_prelude.h"
extern u16 lbl_804CB8C8;

u16 fn_80175E5C(void) {
    u16 temp_r3;

    temp_r3 = lbl_804CB8C8 + 0x8000;
    lbl_804CB8C8 = (lbl_804CB8C8 + 1) & 0x7FFF;
    return temp_r3;
}
