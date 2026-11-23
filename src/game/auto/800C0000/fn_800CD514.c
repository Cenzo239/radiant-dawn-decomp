#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
u8 *fn_80083B84(void*);
void fn_80083DC4(void*, int);
extern u8 lbl_803832E0[0x680];
void fn_800CD514(void) {
    u8 *p = fn_80083B84(lbl_803832E0);
    fn_80083DC4(p, (u8) *(u32 *)(p + 0x60));
}
