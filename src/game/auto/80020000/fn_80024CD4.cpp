#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
struct B { int x; };
struct O : B {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual s16 v18();
};
extern "C" {
s32 fn_80024CD4(O *arg0) {
    return (0x260 - arg0->v18()) >> 1;
}
}
