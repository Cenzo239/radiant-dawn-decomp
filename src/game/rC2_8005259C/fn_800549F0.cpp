#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_800549F0(void* p) {
        int k;
    int d;
    int e;
    Unit2* u;
    int x;
    int y;
    Q10* q;

    q = (Q10*)fn_800CFD3C(&lbl_803E7320);
    u = (Unit2*)fn_800CFB0C(q);
    x = q->x;
    y = q->y;
    k = q->a4;
    d = q->a8;
    e = q->ac;
    fn_8002697C(&lbl_803C8E80);
    if (u) {
        fn_80026CD8(&lbl_803C8E80, (u8*)u, -1);
        fn_8002C170(&lbl_803C8E80);
        if (d) {
            fn_8002BE64(&lbl_803C8E80, d);
        }
        if (((UFull*)u)->flags & 0x10000dc) return;
    }
    switch (k) {
    case 0: fn_800E9380(p, 0); break;
    case 1: fn_800E9380(p, 0); break;
    case 2: fn_800E9380(p, 0); break;
    case 3: fn_800E9458(p, 0); break;
    case 4: fn_800E96E0(p, x, y, e, d, 0); break;
    }
}
