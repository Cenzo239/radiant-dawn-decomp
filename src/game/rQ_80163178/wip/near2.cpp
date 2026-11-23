/* Round 12 attempts that compile but do not match yet. Not compiled by anything. Each section is a whole file. */

#if 0
/* fn_8016BE04: 10 lines, masked diff 2: the original has lis r7 then addi r21,r7 (a separate lis register, also in fn_801662AC), plus a temp swap in the abs terms. */
#include "game/rQ_80163178/common.h"
extern "C" {
void fn_80167704(u8*);
void fn_8010E41C(u8*, int);
u16 fn_801676D8(int, int);
void fn_80166720(Unit*);
void fn_80165F94(Unit*, int, int);
void fn_80165CB0(int, int, Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
int fn_801108F8(Unit*);
}
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
static inline int Ab(int a) { return __abs(a); }
static inline Map* GetM() { return &lbl_803EC898; }
extern "C" u32 fn_8016BE04(Unit* u, Unit* v, s16* ox, s16* oy) {
/*P*/
    Map* m;
    Unit* w;
    int id;
    Unit* lead;
    int bs;
    Unit* b;
    int y;
    int x;
    int r;
    u16 k;
    int y3;
    int x3;
/*E*/
    u8 tbl[0xB];
    m = &lbl_803EC898;
    fn_80167704(v->team);
    lead = 0;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        w = UnitGet(id);
        if (w->person && tbl[w->team[8]] && !MapOutU(m, w) && !(w->flags10C & 0x10000DC) && fn_801676D8(w->x, w->y)) {
            lead = w;
        }
    }
    if (!lead) {
        fn_80166720(u);
        return 0;
    }
    fn_80165F94(lead, 7, lbl_803EC898.w * lbl_803EC898.h);
    bs = 0xFF;
    b = 0;
    for (y = ((Map*)&lbl_803EC898)->y0; y <= ((Map*)&lbl_803EC898)->y1 - 1; y++) {
        for (x = ((Map*)&lbl_803EC898)->x0; x <= ((Map*)&lbl_803EC898)->x1 - 1; x++) {
            if (((Map*)&lbl_803EC898)->cost2S[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40]) {
                w = UnitGet(((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40]);
                if (SameT(lead, w, 1) && m->cost2S[(s8)x + (s8)y * 0x40] < bs) {
                    bs = (u8)m->cost2S[(s8)x + (s8)y * 0x40];
                    b = w;
                }
            }
        }
    }
    if (!b) {
        fn_80166720(u);
        return 0;
    }
    fn_80165CB0(b->x, b->y, v, 7, -1);
    {
        int K = 0x10000;
        k = K - 1;
        r = fn_801108F8(u);
        for (y3 = ((Map*)&lbl_803EC898)->y0; y3 <= lbl_803EC898.y1 - 1; y3++) {
            for (x3 = lbl_803EC898.x0; x3 <= lbl_803EC898.x1 - 1; x3++) {
                if (lbl_803EC898.cost2S[(s8)x3 + (s8)y3 * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x3 + (s8)y3 * 0x40] == 0 && !fn_801658E4(v, (s8)x3, (s8)y3) && lbl_803EC898.ter[0][(s8)x3 + (s8)y3 * 0x40] == 0) {
                    u16 d = fn_801676D8((s8)x3, (s8)y3);
                    int dy = __abs(v->y - y3); if ((u8)r >= (s16)(dy + __abs(v->x - x3)) && d < k) {
                        *ox = x3;
                        k = d;
                        *oy = y3;
                    }
                }
            }
        }
        fn_80166720(u);
        return k != (u16)(K - 1);
    }
}
#endif

#if 0
/* fn_8016B3F4 (and its copy fn_8016B90C): masked diff 30, only colouring: wants i r29, p r28, v r27 above the CSE temps. i1 form below has p = InvAt(u, slot). */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Bs { Unit* u; s8 x; s8 y; u8 k; u8 p7; u32 a; u32 b; };
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
int fn_8016A280(Unit*, Unit*, Inv*, void*, s16*, s16*);
u8* fn_801116B8(Inv*);
int fn_8012B63C(Unit*, u8*);
u8 fn_80127520(Unit*);
void fn_800269E4(void*, void*, void*);
void fn_8002C0EC(void*, int);
s8 fn_80120928(Unit*, Unit*);
s16 fn_80123998(Unit*);
extern const struct Bs lbl_8036B238;
extern const struct Bs lbl_8036B228;
extern u8 lbl_803C8E80[];
void fn_80160610(int, int, int, Unit*, int, int, int, int, int);
}
static inline BOOL HasK(Unit* v, Inv*& q) {
    int i;
    q = v->inv;
    for (i = 0; i < 7; i++, q++) {
        if (!q || !q->item) {
            break;
        }
        if ((*(u32*)(fn_801116B8(q) + 4) & 0x12) && fn_8012B63C(v, q->item)) {
            return 1;
        }
    }
    return 0;
}
extern "C" u32 fn_8016B3F4(Unit* u, int slot, Filter* f, void* arg) {
    Map* m = &lbl_803EC898;
/*P*/
    Unit* v;
    Inv* q;
    u8 bs;
    int ux;
    int rng;
    int x1;
    int x;
    s16 bx;
    s16 by;
    Unit* bv;
    int uy;
    int x0;
    int y1;
    int y;
    int bx2;
/*E*/
    s16 ox;
    s16 oy;
    int s;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    fn_80169C70(u, arg);
    fn_80170B70(u, &u->inv[slot]);
    bv = 0;
    bs = 0;
    uy = u->y;
    ux = u->x;
    bx2 = (u->inv[slot].item ? fn_80110880(u->inv[slot].item, u) : 0);
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
                        if ((lbl_804183F0.flags & 4) || f->check(v)) {
                            if (!((*(u16*)((u8*)v + 0x110) >> 4) & 7) && (*(u16*)((u8*)v->job + 0xEE) & 1) && HasK(v, q)) {
                                if (fn_8016A280(u, v, &u->inv[slot], arg, &ox, &oy)) {
                                    Bs a = {0, 0, 0, 0, 0, 0, 0x1000000};
                                    Bs b = {0, 0, 0, 0, 1, 0, 0x1000000};
                                    b.u = v;
                                    b.x = v->x;
                                    b.y = v->y;
                                    b.k = fn_80127520(v);
                                    a.u = u;
                                    a.x = ox;
                                    a.y = oy;
                                    a.k = slot;
                                    fn_800269E4(lbl_803C8E80, &a, &b);
                                    fn_8002C0EC(lbl_803C8E80, (s8)slot);
                                    s = fn_80120928(u, v);
                                    if (s >= 5 && bs <= s + fn_80123998(v)) {
                                        bs = s + fn_80123998(v);
                                        bx = ox;
                                        by = oy;
                                        bv = v;
                                    }
                                }
                            }
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
        u->h3BE = bs;
    }
    return bv != 0;
}
#endif

#if 0
/* fn_8016EDE8: 3 lines: the ter pointer temp should share r18 with v, and gets r16. */
#include "game/rQ_80163178/common.h"
extern "C" {
void fn_80165E18(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
int fn_8011EFC8(Unit*, Unit*);
int fn_8016CB60(Unit*, Inv*);
}
static inline BOOL HasW(Unit* u, Unit* v) {
    int i;
    BOOL any = 0;
    Inv* p = v->inv;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8016CB60(u, p)) {
            any = 1;
            break;
        }
    }
    return any;
}
extern "C" u32 fn_8016EDE8(Filter* f, Unit* u, s16* ox, s16* oy) {
/*P*/
    s16 best;
    s16 bx;
    s16 by;
    int y;
    int x;
    Unit* v;
/*E*/
    best = 0x7FFF;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v) && fn_8011EFC8(u, v) && HasW(u, v)) {
                    if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                        best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                        bx = x;
                        by = y;
                    }
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}
#endif

#if 0
/* fn_8016FEE8: 293 by position: hand-written xe/ye reproduce the stepped x+r and y+r, but x+r gets hoisted; the original keeps it in r14 with an add at the x loop head. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
void fn_80165B48(int, int, Unit*, int, int);
void fn_80165CB0(int, int, Unit*, int, int);
void fn_80165AD4(int, int, int, u8*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
u16 fn_801676D8(int, int);
int fn_80165818(void);
void fn_801148CC(Map*, int);
}
static inline s16 CostAt(Unit* u, int x, int y) {
    if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < 0) {
        return 0x7FFF;
    }
    return lbl_803EC898.cost2S[u->x + u->y * 0x40];
}
static inline int Safe(Unit* u, int x, int y, int xe, int ye, Filter* f, int r) {
                        int xx0, xx1, yy, yy1, xx;
                        xx0 = x - r;
                        if (xx0 < lbl_803EC898.x0) {
                            xx0 = lbl_803EC898.x0;
                        }
                        yy = y - r;
                        if (yy < lbl_803EC898.y0) {
                            yy = lbl_803EC898.y0;
                        }
                        xx1 = xe;
                        if (xx1 > lbl_803EC898.x1 - 1) {
                            xx1 = lbl_803EC898.x1 - 1;
                        }
                        yy1 = ye;
                        if (yy1 > lbl_803EC898.y1 - 1) {
                            yy1 = lbl_803EC898.y1 - 1;
                        }
                        for (; yy <= yy1; yy++) {
                            for (xx = xx0; xx <= xx1; xx++) {
                                if (r >= ABS(x - xx) + ABS(y - yy)) {
                                    u8 t2 = lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40];
                                    if (t2 && f->check(UnitGet(t2))) {
                                        fn_801148CC(&lbl_803EC898, fn_80165818());
                                        fn_80165AD4(xx, yy, 0, u->team, 0xC, lbl_803EC898.w * lbl_803EC898.h);
                                        if (lbl_803EC898.curS[(s8)x + (s8)y * 0x40] <= r) {
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
    return 1;
}
extern "C" void fn_8016FEE8(Unit* u, int x_, int y_, Filter* f, int r, u8 act, u16 thr, int fl, u8 f9, int rng) {
/*P*/
    int y;
    int x;
    int ok;
    int xe;
    int ye;
    s16 bx;
    s16 b22;
    s16 d;
    s16 d24;
    s16 by;
    u16 bd;
    s16 ax;
    s16 ay;
    s16 cx;
    s16 cy;
    int ux;
    int uy;
    int x0;
    int x1;
    int y1;
/*E*/
    if (fl) {
        fn_80165B48(x_, y_, u, 7, lbl_803EC898.w * lbl_803EC898.h);
    } else {
        fn_80165CB0(x_, y_, u, 7, lbl_803EC898.w * lbl_803EC898.h);
    }
    d = CostAt(u, x_, y_);
    ux = u->x;
    uy = u->y;
    bd = 0xFFFF;
    d24 = -1;
    bx = -1;
    b22 = 0x7FFF;
    if (rng < 0) {
        rng = fn_8012408C(u);
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
    for (ye = y + r; y <= y1; ye++, y++) {
        for (x = x0, xe = x + r; x <= x1; xe++, x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y)) {
                    u8 t = lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40];
                    if ((t == 0 || t == u->tid) && lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40] >= 0) {
                        ok = Safe(u, x, y, xe, ye, f, r);
                        if (ok) {
                            if (thr < fn_801676D8((s8)x, (s8)y)) {
                                if (bd > fn_801676D8((s8)x, (s8)y)) {
                                    bd = fn_801676D8((s8)x, (s8)y);
                                    ax = x;
                                    ay = y;
                                }
                            } else {
                                s16 c = lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                                if (d < c) {
                                    if (b22 > c) {
                                        b22 = c;
                                        cx = x;
                                        cy = y;
                                    }
                                } else if (c < d || fn_801676D8((s8)x, (s8)y) < d24) {
                                    d = lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                                    d24 = fn_801676D8((s8)x, (s8)y);
                                    bx = x;
                                    by = y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bx != -1) {
        fn_80160610(act, (s8)bx, (s8)by, 0, (s8)bx, (s8)by, -1, 0, 0);
    } else if (f9 && b22 != 0x7FFF) {
        fn_80160610(act, (s8)cx, (s8)cy, 0, (s8)cx, (s8)cy, -1, 0, 0);
    } else if (f9 && bd != 0xFFFF) {
        fn_80160610(act, (s8)ax, (s8)ay, 0, (s8)ax, (s8)ay, -1, 0, 0);
    }
}
#endif
