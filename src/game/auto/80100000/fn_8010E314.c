#include "game/auto/m2c_prelude.h"
s32 * fn_80060728();
extern u8 lbl_803CAB38[0x988];

s32 fn_8010E314(u32 arg0, u32 arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if ((u32) (*fn_80060728(lbl_803CAB38) & 3) == 2) {
        return 1;
    }
    if ((arg0 == 1U) || (arg1 == 1U)) {
        return 1;
    }
    return 2;
}
