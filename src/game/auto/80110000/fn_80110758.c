#include "game/auto/m2c_prelude.h"
s32 fn_80110758(u32 arg0) {
    if ((arg0 >= 6U) && (arg0 <= 0xAU)) {
        return 1;
    }
    if (arg0 == 0x10U) {
        return 1;
    }
    if (arg0 == 0x11U) {
        return 1;
    }
    return (arg0 - 0x12) == 0;
}
