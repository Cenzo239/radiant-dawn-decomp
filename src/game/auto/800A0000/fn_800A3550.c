#include "game/auto/m2c_prelude.h"
u32 * fn_80060728();
extern u8 lbl_803CAB38[0x988];

s32 fn_800A3550(void) {
    return (((u32) *fn_80060728(lbl_803CAB38) >> 0x11U) & 1) ^ 1;
}
