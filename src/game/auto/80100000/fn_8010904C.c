#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
typedef struct { u16 a; u16 b : 8; u16 c : 8; } BF;
void fn_8010904C(BF *p) {
    p->a = (u32)p->a & 0xFFFF0000;
    p->b = 0;
}
