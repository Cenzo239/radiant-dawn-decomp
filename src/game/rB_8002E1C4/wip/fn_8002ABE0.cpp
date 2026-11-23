/* NEAR MISS: fn_8002ABE0 (24 words: `lhz -0x2e72` form needs lbl.member, which flips the lis colouring; ((MapS*)&lbl)-> gets colouring but lhzx) and fn_8002D8D8 (24 words: only u r29 and nx/o r28 swapped). fn_8002AAEC and fn_8002DBA0 from this file are matched in fn_8002AAEC.cpp. */
#define lbl_803C8E80 lbl_unused
#include "game/rB_8002E1C4/battle.h"
#undef lbl_803C8E80

struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};
struct Roll { u8 pad[0xa3]; u8 xa3; };
extern MapS lbl_803EC898;
#define M ((MapS*)&lbl_803EC898)
extern Roll lbl_803C8DA0;
extern const char lbl_80361338[];
extern u8* lbl_804CB810;
extern void* lbl_804CA590;
extern void* lbl_804CA6DC;
extern const f32 lbl_804CCCC8;
extern const f64 lbl_804CCCD8;
extern const f64 lbl_804CCCE0;
extern "C" {
u8* fn_80116A30(MapS* m, s8 x, s8 y);
f32 fn_80117200(MapS* m, s8 x, s8 y, u8 c);
int fn_801148D8(MapS* m, int n);
void* fn_80078D9C(int n, const char* s, int k);
void fn_80078E24(void* p);
void fn_80114944(MapS* m, int n, void* p);
void fn_80114A44(MapS* m, int n, void* p);
void fn_801148CC(MapS* m, void* p);
void fn_80114B44(MapS* m, int a, int b);
void fn_80114888(MapS* m, int n);
Slot* fn_80030CBC(BU* p);
ItemD* fn_801116B8(Slot* it);
int fn_801107C0(void* d, BU* u);
int fn_801107A0(void* d, BU* u);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
f32 fn_80114230(MapS* m, s8 x, s8 y);
int fn_8011799C(MapS* m, s8 x, s8 y);
int fn_8011B77C(void* list, void* key);
Unit* fn_80127B68(Unit* u);
Unit* fn_8012E3A4(Unit* u);
f32 fn_80127868(Unit* u);
Rec7 fn_801278B8(Unit* u, f32 bio);
int fn_8012E9B4(Unit* a, Unit* b);
u8 fn_8012E8BC(Unit* a, s8 k);
int fn_80089D68(int n);
int fn_800262A8(void* log, int k);
void fn_80126EB0(Unit* u, s8 x, s8 y);
void fn_800269E4(Battle* b, const Spec& a, const Spec& d);
void fn_8002E6FC(BU* p, Unit* u);
void fn_8002B2AC(Battle* b, int a, int k);
extern Battle lbl_803C8E80;
#define BT (&lbl_803C8E80)

int fn_8002AAEC(BU* a, BU* d) {
    u8* r = fn_80116A30(M, d->u.x102, d->u.y103);
    s8 x = a->u.x102;
    s8 y = a->u.y103;
    u8 c = *r;
    f32 k = lbl_804CCCC8;
    while (!(c & 0x40)) {
        if (k <= (f32)__fabs(fn_80117200(M, x, y, c))) return 1;
        if (c & 1) x--;
        else if (c & 2) x++;
        else if (c & 4) y++;
        else if (c & 8) y--;
        c = *++r;
    }
    return 0;
}

static inline u8 rmax(Slot* w, BU* a) {
    if (w->data) return fn_801107C0(w->data, a);
    return 0;
}
static inline u8 rmin(Slot* w, BU* a) {
    if (w->data) return fn_801107A0(w->data, a);
    return 0;
}
struct WS { u16 v; };
static inline u16 mapP(u16* p) { return *p; }
static inline u16 mapR(const u16& p) { return p; }
static inline u16 mapS(MapS* m, s8 x, s8 y) { u16* p = &m->xd18e[x + y * 64]; return *p; }
static inline u16 mapT(s8 x, s8 y) { u16* p = &((MapS*)&lbl_803EC898)->xd18e[x + y * 64]; return *p; }
static inline void check(Battle* b, BU* a, BU* d, void* buf1, int& r) {
    Slot* w = fn_80030CBC(a);
    if (w->data && b->f15e8 > 1 && !(fn_801116B8(w)->flags & 0x5000)) {
        fn_801148CC(M, buf1);
        fn_80114B44(M, 9, 0);
        {
        u8 mx = rmax(w, a);
        fn_80115DEC(M, a->u.x102, a->u.y103, rmin(w, a), mx);
        }
        if (M->xd18e[d->u.x102 + d->u.y103 * 64] && fn_8002AAEC(a, d)) {
            s8 x, y;
            f32 f;
            y = a->u.y103;
            x = a->u.x102;
            f = fn_80114230(M, d->u.x102, d->u.y103);
            f32 v = -(fn_80114230(M, x, y) - f);
            if (lbl_804CCCD8 <= v) a->s47e = 1;
            else if (lbl_804CCCE0 >= v) a->s47e = -1;
            else a->s47e = 0;
            r = 1;
        }
    }
}

void fn_8002ABE0(Battle* b, BU* a, BU* d) {
    int r = 0;
    void* buf1 = fn_80078D9C(-fn_801148D8(M, 7), lbl_80361338, 0);
    void* buf2 = fn_80078D9C(-fn_801148D8(M, 9), lbl_80361338, 0);
    fn_80114944(M, 9, buf2);
    check(b, a, d, buf1, r);
    check(b, d, a, buf1, r);
    if (r) b->f15ec |= 0x1000000;
    fn_80114888(M, 7);
    fn_80114A44(M, 9, buf2);
    fn_80078E24(buf2);
    fn_80078E24(buf1);
}

static inline int dirOf(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    }
    return 0x40;
}
static inline int dxOf(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int dyOf(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
static inline Unit* byId(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}
static inline int rollP(int n) {
    if (lbl_803C8E80.f15ec & 0x4000) {
        if (lbl_803C8DA0.xa3) return 1;
        return 0;
    }
    return fn_80089D68(n);
}

#pragma use_lmw_stmw on
Unit* fn_8002D8D8(Battle* b) {
    Unit* u;
    int nx;
    Unit* o;
    int ux;
    int uy;
    int i;
    u = b->b.u.u3f0;
    if (u == 0) return 0;
    {
    ux = u->x102;
    uy = u->y103;
    for (i = 0; i < 4; i++) {
        int d = dirOf(i);
        nx = ux + dxOf(d);
        int ny = uy + dyOf(d);
        if (fn_8011799C(M, nx, ny)) {
            u8 id = M->grid[(s8)nx + (s8)ny * 64];
            if (id) {
                o = byId(id);
                if (o->f4[8] == u->f4[8]) {
                    if (fn_8011B77C(o->x12c, lbl_804CA590) && u == fn_80127B68(o)) return o;
                    if (fn_8012E3A4(u) == o && fn_8011B77C(o->x12c, lbl_804CA6DC)) {
                        f32 bioA = fn_80127868(o);
                        {
                        Rec7 r = fn_801278B8(o, bioA);
                        int p = r.f;
                        switch (fn_8012E8BC(u, fn_8012E9B4(u, o))) {
                        case 1: p += 15; break;
                        case 2: p += 20; break;
                        case 3: p += 25; break;
                        }
                        if (p < 0) p = 0;
/*ROLL*/
                        if (rollP(p)) return o;
                        }
                    }
                }
            }
        }
    }
    }
    return 0;
}

int fn_8002DBA0(Battle* b, int k) {
    if (fn_800262A8(b->log, 0x16)) {
    Unit* a = b->a.u.u3f0;
    Unit* t = b->b.u.u3f0;
    Unit* c = fn_8002D8D8(b);
    if (c) {
    int tx, ty, cx, cy;
    cx = c->x102;
    cy = c->y103;
    tx = t->x102;
    ty = t->y103;
    fn_80126EB0(t, cx, cy);
    fn_80126EB0(c, tx, ty);
    {
        Spec sd = {c, c->x102, c->y103, -1, 0, 0, 1};
        Spec sa = {a, a->x102, a->y103, -1, 0, 0, 1};
        fn_800269E4(BT, sa, sd);
    }
    BT->b.x481 = 1;
    fn_8002E6FC(&BT->c, t);
    BT->f15ec |= 0x40000;
    fn_8002B2AC(BT, k, 0);
    fn_80126EB0(t, tx, ty);
    fn_80126EB0(c, cx, cy);
    return 1;
    }
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
