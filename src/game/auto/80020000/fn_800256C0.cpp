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
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual s32 vcall();
};
extern "C" {
void fn_80083DC4(s8*,s32);
#if TARGET_PC
FE10_PROTO p32ret fn_800D0864(u8*, ...);
#else
s32 fn_800D0864(u8*,u8*);
#endif
void fn_80283A58();
extern u8 lbl_80361260[0xa8];
extern VObj *lbl_804CB5B8;
extern s32 lbl_804CB700;

void fn_800256C0(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x34) = fn_800D0864(lbl_80361260 + 0x2C, lbl_80361260);
    if (lbl_804CB5B8->vcall() & 0xC00) {
        fn_80283A58();
        lbl_804CB700 &= 0xFFDFFEFF;
        fn_80083DC4(arg0, 6);
    }
}


}
