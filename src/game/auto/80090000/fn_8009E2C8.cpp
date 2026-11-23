#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class VObj {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual s32 v16();
};
extern "C" {
#if TARGET_PC
FE10_PROTO void fn_80081194(u8*, p32arg);
#else
void fn_80081194(u8*, s32);
#endif
extern u8 lbl_80381B58[0x28];
extern VObj *lbl_804CB5B8;
extern s32 lbl_804CB700;

void fn_8009E2C8(s32 arg0) {
    if (!(lbl_804CB700 & 0x84) && (lbl_804CB5B8->v16() & 0x4000)) {
        fn_80081194(lbl_80381B58, arg0);
    }
}
}
