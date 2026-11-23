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
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12(s32);
};
extern "C" {
void fn_80201040(VObj *arg0, s32 arg1) {
    arg0->v11();
    arg0->v12(arg1);
}
}
