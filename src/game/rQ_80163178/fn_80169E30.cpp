#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80165F94(Unit*, int, int);
void fn_80169C70(Unit*, void*);
void fn_80170B70(Unit*, Inv*);
u8 fn_80110880(u8*, Unit*);
s8 fn_8012408C(Unit*);
int fn_80108F68(void*);
u8 fn_80126BA4(Unit*);
int fn_8016D11C(Unit*);
BOOL fn_80169B20(Unit*, u16, int, int, void*, s16*, s16*);
void fn_8012A088(Unit*, int);
s16 fn_801237EC(Unit*);
void fn_80160610(int, int, int, Unit*, int, int, int, int, int);
}
#pragma use_lmw_stmw off
extern "C" u32 fn_80169E30(Unit* u, int slot, Filter* f, void* arg) {
    Map* m = &lbl_803EC898;
    s16 bx;
    int bs;
    s16 by;
    Unit* bv;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    Unit* v;
    int uy;
    int x0;
    int y1;
    Inv* p;
    int bx2;
    int pct;
    s16 ox;
    s16 oy;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    fn_80169C70(u, arg);
    p = &u->inv[slot];
    fn_80170B70(u, p);
    uy = u->y;
    bs = 100;
    bv = 0;
    ux = u->x;
    bx2 = (p->item ? fn_80110880(p->item, u) : 0);
    {
        int b = fn_8012408C(u);
        rng = b + bx2;
    }
    x0 = ux - rng;
    if (x0 < lbl_803EC898.x0) {
        x0 = lbl_803EC898.x0;
    }
    y = uy - rng;
    if (y < lbl_803EC898.y0) {
        y = lbl_803EC898.y0;
    }
    x1 = ux + rng;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + rng;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (m->g4[(s8)x + (s8)y * 0x40]) {
                    u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
                    if (t && t != u->tid) {
                        v = UnitGet(t);
                        if (!((lbl_804183F0.flags & 4) == 0 && f->check(v))) {
                            if (v->w3B4 & 1) { s16 mx = fn_801237EC(v); pct = 100.0f * v->hp / mx; if ((u8)pct <= (u8)bs) {
                                if (fn_80169B20(u, fn_8016D11C(u), (s16)x, (s16)y, arg, &ox, &oy)) {
                                    bs = pct;
                                    bx = ox;
                                    by = oy;
                                    bv = v;
                                }
                            }}
                        }
                    }
                }
            }
        }
    }
    if (bv) {
        if (slot >= 0 && slot < 7) {
            fn_8012A088(u, slot);
            slot = 0;
        }
        fn_80160610(0x10, (s8)bx, (s8)by, bv, bv->x, (s8)*(u8*)&bv->y, (s8)slot, 0, 0);
        u->h3BE = 100 - (u8)bs;
    }
    return bv != 0;
}
