#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct PadBase { u8 pad[0x44]; };
class VObj : public PadBase {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual s32 vcall();
};
extern "C" {
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(p32arg, s32);
#else
void fn_8023F1A0(s32, s32);
#endif
void fn_800CE018(VObj *arg0) {
    fn_8023F1A0(arg0->vcall(), 0x400);
}
}
