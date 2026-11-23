#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct S { s32 a; u8 *p; };

void fn_8008A5C0(struct S *arg0, u16 arg1) {
    *arg0->p++ = (u8) (arg1 >> 8);
    *arg0->p++ = (u8) arg1;
}
