#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" int fn_80054D98(void* parent, u8 n) {
    u8 buf[24];
    int i;
    fn_800CFB34(&lbl_803E7320);
    fn_8010E41C(buf, 0);
    for (i = 1; i <= 0xfe; i++) {
        UFull* u = GetU(i);
        if (u->ec == 0) continue;
        if (!buf[u->f4->b8]) continue;
        if (!fn_80108D00(u->sk, n) || (u->flags & 0x10000dc)) {
            fn_80108E20(u->sk, n);
        } else {
            fn_800CFC50(&lbl_803E7320, u->x, u->y, u->fc, n);
        }
    }
    if (lbl_803E7320.i0 == 0) {
        return 0;
    }
    fn_80081194(lbl_8037DE20, parent);
    return 1;
}
