#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public: virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14(); virtual int s15(); virtual int s16(); };
extern "C" {
#if TARGET_PC
FE10_PROTO void fn_80083DC4(p32arg, s32);
#else
void fn_80083DC4(s32, s32);
#endif
s8 *fn_8024BCA0();
extern V *lbl_804CB5B8;
void fn_8009C4CC(s32 arg0) {
    if (((u8) M2C_FIELD(fn_8024BCA0(), u8 *, 0x34) > 1U) && (lbl_804CB5B8->s16() & 0x4000)) {
        fn_80083DC4(arg0, 0x63);
    }
}
}
