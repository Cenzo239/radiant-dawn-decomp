#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class VObj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 v4();
    virtual void v5();
};
extern "C" {
#if TARGET_PC
FE10_PROTO p32ret fn_8024BC94(void);
#else
s32 fn_8024BC94();
#endif
#if TARGET_PC
FE10_PROTO s32 fn_802454C8(p32arg, s32);
FE10_PROTO void fn_8024542C(p32arg, s32);
#else
s32 fn_802454C8(s32, s32);
void fn_8024542C(s32, s32);
#endif
s32 fn_800CD7F4(VObj *arg0) {
    s8 *temp_r31;
    s32 x;

    if ((arg0 == NULL) || (arg0->v4() == 0) || (temp_r31 = M2C_FIELD(arg0, s8 **, 0xC), (((s16) M2C_FIELD(temp_r31, s16 *, 0x22) < 0) != 0))) {
        return 1;
    }
    x = fn_8024BC94();
    if (fn_802454C8(x, M2C_FIELD(temp_r31, s16 *, 0x22)) == 0) {
        x = fn_8024BC94();
        fn_8024542C(x, M2C_FIELD(temp_r31, s16 *, 0x22));
    }
    return 1;
}
}
