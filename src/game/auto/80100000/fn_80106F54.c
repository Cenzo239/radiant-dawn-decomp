#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80062A9C(void *, unsigned int);
#else
s32 * fn_80062A9C();
#endif
extern u8 lbl_803CAB38[0x988];

s32 fn_80106F54(u8 *arg0) {
    s32 *temp_r3;

    temp_r3 = fn_80062A9C(lbl_803CAB38, *arg0);
    if (temp_r3 == NULL) {
        return 0;
    }
    return *temp_r3;
}
