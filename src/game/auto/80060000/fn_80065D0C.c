#include "game/auto/m2c_prelude.h"
M2C_UNK __register_global_object();
M2C_UNK fn_8028BFD8();
extern u8 fn_80065D64[0x34];
extern u8 fn_80065D98[0x5c];
extern u8 fn_80065DF4[0x1c];
extern u8 lbl_803CB4C0[0x10];
extern u8 lbl_803CB4D0[0x2a0];

void fn_80065D0C(void) {
    fn_8028BFD8(lbl_803CB4D0, fn_80065D64, fn_80065D98, 0x30, 0xE);
    __register_global_object(0, fn_80065DF4, lbl_803CB4C0);
}
