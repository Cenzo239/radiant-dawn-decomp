#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class VObj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void vcall();
};
extern "C" {
void fn_801DCB44(s32, s32, s32, s32, s32);
void fn_80240C70(s8 *arg0) {
    ((VObj *) arg0)->vcall();
    fn_801DCB44(0, 0, (s16) (M2C_FIELD(arg0, s16 *, 0xE) - M2C_FIELD(arg0, s16 *, 0xA)), (s16) (M2C_FIELD(arg0, s16 *, 0x10) - M2C_FIELD(arg0, s16 *, 0xC)), M2C_FIELD(arg0, s32 *, 0x38));
}
}
