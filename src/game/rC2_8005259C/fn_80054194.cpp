#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" int fn_80054194(void* parent) {
    u8 buf[24];
    int i;
    fn_800CFB34(&lbl_803E7320);
    fn_8010E41C(buf, 0);
    for (i = 1; i <= 0xfe; i++) {
        UFull* u = GetU(i);
        if (u->ec && buf[u->f4->b8] && !(u->flags & 4) && fn_8011799C(lbl_803EC898, u->x, u->y) && *(s16*)lbl_803CAB38.pad12 > 1 && fn_80128744((Unit2*)u) && !fn_801284C4((Unit2*)u)) {
            fn_800CFC50(&lbl_803E7320, u->x, u->y, u->fc, 0);
        }
    }
    if (lbl_803E7320.i0 != 0) {
        fn_80081194(lbl_8037DD48, parent);
        return 1;
    }
    return 0;
}
