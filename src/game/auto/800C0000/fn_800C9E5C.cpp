#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public:
 virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5();
 virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14(); };
extern "C" {
s32 fn_800C9E5C(V *arg0) {
    s32 temp_r31;
    temp_r31 = arg0->s14();
    return arg0->s10() / temp_r31;
}
}
