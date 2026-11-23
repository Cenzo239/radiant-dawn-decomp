#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void* fn_80062A9C(void*, int);
extern u8 lbl_803CAB38[0x988];
int fn_80106F10(u8 *arg0) {
    u8 *t = fn_80062A9C(lbl_803CAB38, *arg0);
    if (t == NULL) {
        return -1;
    }
    return t[7];
}
