#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct O {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual s32 v7();
    s32 x;
};
extern "C" {
#if TARGET_PC
FE10_PROTO u16** fn_80006A0C(p32arg, s32);
#else
u16** fn_80006A0C(s32, s32);
#endif
u16 fn_800C9D68(O *arg0) {
    return (*fn_80006A0C(arg0->x, arg0->v7()))[1];
}
}
