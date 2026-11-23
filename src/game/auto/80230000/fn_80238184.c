#include "game/auto/m2c_prelude.h"
s32 fn_8031D34C();
extern u8 lbl_804230E8[0x38];

s32 fn_80238184(s32 arg0) {
    s32 sp8;

    if (fn_8031D34C(lbl_804230E8, &sp8, arg0) == 1) {
        return sp8;
    }
    return 0;
}
