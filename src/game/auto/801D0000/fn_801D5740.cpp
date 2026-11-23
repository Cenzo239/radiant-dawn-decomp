#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
extern "C" {
void fn_801D77BC(int, int, int);
void fn_801D5740(O *arg0) {
    arg0->v3();
    fn_801D77BC(0, 0, 0x10);
}
}
