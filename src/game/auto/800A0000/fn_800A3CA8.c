#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, u8);
#else
void fn_80083DC4(int, u8);
#endif
extern u8 lbl_804CB630;

void fn_800A3CA8(int a) {
    fn_80083DC4(a, lbl_804CB630);
}
