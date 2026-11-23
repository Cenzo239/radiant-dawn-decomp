#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_80054F4C(E3x* e) {
    WW* w = (WW*)fn_800CFD3C(&lbl_803E7320);
    int n;
    fn_80027088(&lbl_803C8E80, fn_800CFB0C(w), -1);
    fn_8002C170(&lbl_803C8E80);
    n = e->h34 - ((s16*)&lbl_803C8E80)[0x44a/2];
    n /= w->b;
    if (n > fn_801237EC(&lbl_803C8E80)) n = fn_801237EC(&lbl_803C8E80);
    if (n < 1) n = 1;
    e->b3b = n != 0;
    fn_8002BE64(&lbl_803C8E80, -n);
    fn_800E9608(e, 0);
}
