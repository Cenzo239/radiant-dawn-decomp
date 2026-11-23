#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public: virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); int f; };
extern "C" {
#if TARGET_PC
FE10_PROTO u16 ** fn_80006A0C(p32arg, int);
#else
u16 **fn_80006A0C(int, int);
#endif
u16 fn_800C9DB4(V *arg0) {
    return **fn_80006A0C(arg0->f, arg0->s7());
}
}
