#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class VObj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual s32 v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual s32 v13();
};
extern "C" {
s32 fn_800C9E00(VObj *arg0) {
    s32 t;
    t = arg0->v13();
    return arg0->v9() / t;
}
}
