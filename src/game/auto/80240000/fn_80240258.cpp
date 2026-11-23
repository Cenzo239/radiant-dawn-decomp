#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V { public: virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); };
extern "C" {
void fn_801DC984(s32, s32, s32, s32);
void fn_80240258(V *arg0) {
    arg0->s3();
    fn_801DC984(0, 0, (s16) (M2C_FIELD(arg0, s16 *, 0xE) - M2C_FIELD(arg0, s16 *, 0xA)), M2C_FIELD(arg0, s32 *, 0x38));
}
}
