#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public:
 virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5();
 virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(s32); };
extern "C" {
void fn_80200DAC(V *arg0, s32 arg1) {
    arg0->s10();
    arg0->s11(arg1);
}
}
