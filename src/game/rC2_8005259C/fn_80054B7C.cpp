#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_80054B7C(void) {
    int t;
    U5* u = (U5*)fn_800CFB0C(fn_800CFD3C(&lbl_803E7320));
    if (u) {
        t = 0;
        u8 k = u->f4->b8;
        if (!fn_8011B77C(u->x12c, lbl_804CA58C) && !u->b114) {
            t = 1;
        }
        fn_8011E414(u);
        if (t) {
            switch (k) {
            case 0: GD->c8++; GD->hc0++; break;
            case 1: GD->cc++; GD->hc2++; u->h384++; u->h386++; break;
            case 2: GD->d0++; GD->hc4++; break;
            case 3: GD->d4++; GD->hc6++; break;
            }
        }
    }
}
