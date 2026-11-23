#include "game/auto/m2c_prelude.h"
M2C_UNK __register_global_object();
extern u8 fn_8014C9F8[0x6c];
extern u8 lbl_804181A0[0xc];
extern u8 lbl_804181AC[0x244];
extern s32 lbl_804CB878;

void fn_8014C9C8(void) {
    lbl_804CB878 = 0;
    M2C_FIELD(lbl_804181AC, s32 *, 4) = 0;
    M2C_FIELD(lbl_804181AC, s32 *, 8) = 0;
    M2C_FIELD(lbl_804181AC, s32 *, 0xC) = 0;
    __register_global_object(lbl_804181AC, fn_8014C9F8, lbl_804181A0);
}
