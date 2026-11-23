#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct PadBase { u8 pad[0x44]; };
class VObj : public PadBase {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
};
extern "C" {
void fn_800CE168(VObj *arg0) {
    arg0->v3();
    arg0->v1();
}
}
