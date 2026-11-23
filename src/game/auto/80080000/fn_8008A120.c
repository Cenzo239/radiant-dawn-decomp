#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80320D68();
M2C_UNK fn_80320E24();
extern u8 fn_8008A0F0[0x18];
extern u8 fn_8008A108[0x18];
extern s16 lbl_804CA3C8;

void fn_8008A120(void) {
    lbl_804CA3C8 = -1;
    fn_80320E24(fn_8008A0F0);
    fn_80320D68(fn_8008A108);
}
