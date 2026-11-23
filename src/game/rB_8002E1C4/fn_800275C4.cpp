#include "game/rB_8002E1C4/battle.h"

/* Pre-round setup for one exchange, and the triangle-attack partner search. */
struct ItemF { union { u64 ll; struct { u32 hi, lo; }; }; u8 pad[0x12 - 8]; u8 x12; };
struct TriB { u8 pad[0x15f0]; Unit* t[3]; };
struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};
extern MapS lbl_803EC898;
#define M ((MapS*)&lbl_803EC898)
extern Unit** lbl_804CB814;
extern void* lbl_804CA5B0;
extern void* lbl_804CA5B4;
extern void* lbl_804CA4E0;
extern void* lbl_804CA4E4;
extern void* lbl_804CA6A8;
extern void* lbl_804CA63C;
extern void* lbl_804CA6F4;
extern void* lbl_804CA69C;
extern void* lbl_804CA6F0;
extern void* lbl_804CA698;
extern "C" {
int fn_8011B77C(void* list, void* key);
int fn_8010931C(void* p);
u8 fn_80126F34(Unit* u, BU* d);
int fn_80116DB8(MapS* m, s8 x, s8 y, s8 a, s8 b);
Slot* fn_8012759C(Unit* u);
int fn_801107C0(void* d, Unit* u);
int fn_801107A0(void* d, Unit* u);
void fn_80114888(MapS* m, int n);
void fn_80114B44(MapS* m, int a, int b);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
int fn_8002D348(Unit** v, int n, BU* u);
void fn_80026208(void* log, int k);
void fn_80026288(void* log);
void fn_8002600C(void* log, int code, int v);
Slot* fn_80030CBC(BU* p);
int fn_8011F2F0(BU* a, BU* b);
void fn_80110D38(Slot* s);
int fn_800300B4(BU* p);
void fn_8003065C(BU* p);
ItemF* fn_801116B8(Slot* s);
void fn_8002F20C(BU* p);

static inline u8 kind(Slot* s) {
    if (s->data) return ((ItemF*)s->data)->x12;
    return 0x13;
}
static inline u8 uMin(Slot* s, Unit* u) {
    if (s->data) return fn_801107A0(s->data, u);
    return 0;
}
static inline u8 uMax(Slot* s, Unit* u) {
    if (s->data) return fn_801107C0(s->data, u);
    return 0;
}
static inline u8 itemKind(ItemF* d) {
    if (d) return d->x12;
    return 0x13;
}

#pragma use_lmw_stmw on
int fn_8002D430(BU* a) {
    Unit* list[4];
    Unit* found[4];
    if (a->u.f4[8] != 0) return 0;
    if (fn_8011B77C(a->u.x12c, lbl_804CA5B0)) {
        int n = 1;
        Unit* next;
        Unit* u;
        list[0] = a->u.u3f0;
        for (u = *lbl_804CB814; u; ) {
            next = u->next;
            if (u != a->u.u3f0 && fn_8011B77C(u->x12c, lbl_804CA5B0) && n < 4) {
                list[n++] = u;
            }
            u = next;
        }
        if (n < 3) return 0;
        {
        Unit** p = list;
        int c = 0;
        int i;
        for (i = 0; i < n; p++, i++) {
            if (i > 0 && c == 0) return 0;
            if (!((*p)->f10c & 0x10000dc) && !fn_8010931C((*p)->x110)
                && (fn_8011B77C((*p)->x12c, lbl_804CA4E0) || fn_8011B77C((*p)->x12c, lbl_804CA4E4))
                && fn_80126F34(*p, (BU*)(a + 1)) == 1
                && fn_80116DB8(M, (*p)->x102, (*p)->y103, (a + 1)->u.x102, (a + 1)->u.y103)) {
                Slot* w = fn_8012759C(*p);
                if (w && w->data && uMin(w, *p) <= 1) {
                    found[c++] = *p;
                    if (c == 3) break;
                }
            }
        }
        if (c < 3) return 0;
        }
    } else if (fn_8011B77C(a->u.x12c, lbl_804CA5B4)) {
        int n = 1;
        Unit* next;
        Unit* u;
        list[0] = a->u.u3f0;
        for (u = *lbl_804CB814; u; ) {
            next = u->next;
            if (u != a->u.u3f0 && fn_8011B77C(u->x12c, lbl_804CA5B4) && n < 4) {
                list[n++] = u;
            }
            u = next;
        }
        if (n < 3) return 0;
        {
        int c = 0;
        Unit** p = list;
        int i;
        for (i = 0; i < n; p++, i++) {
            if (i > 0 && c == 0) return 0;
            if (!((*p)->f10c & 0x10000dc) && !fn_8010931C((*p)->x110)) {
                Slot* w = fn_8012759C(*p);
                if (w && w->data) {
                    ItemF* d = (ItemF*)w->data;
                    if (itemKind(d) == 3 || itemKind(d) == 0xd) {
                        fn_80114888(M, 7);
                        fn_80114B44(M, 9, 0);
                        {
                        u8 mx = uMax(w, *p);
                        fn_80115DEC(M, (*p)->x102, (*p)->y103, uMin(w, *p), mx);
                        }
                        if (M->xd18e[(a + 1)->u.x102 + (a + 1)->u.y103 * 64]) {
                            found[c++] = *p;
                        }
                    }
                }
            }
        }
        if (c < 3) return 0;
        if (fn_8002D348(found, c, a + 1) == 0) return 0;
        }
    } else {
        return 0;
    }
    {
        int k = 0;
        for (int i = 0; i < 3; i++) {
            if (found[i] != a->u.u3f0) ((TriB*)a)->t[k++] = found[i];
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset

static inline void ranged(BU* u) {
    if (fn_80030CBC(u)->data && (kind(fn_80030CBC(u)) == 0xb || kind(fn_80030CBC(u)) == 0xd)) fn_8003065C(u);
}
static inline void flag4000(BU* u) {
    if (fn_801116B8(fn_80030CBC(u))->lo & 0x1000) fn_8003065C(u);
}
static inline void far1(BU* u) {
    if (kind(fn_80030CBC(u)) != 3 && !(fn_801116B8(fn_80030CBC(u))->lo & 2)) fn_8003065C(u);
}
static inline void far2(BU* u) {
    if (fn_801116B8(fn_80030CBC(u))->ll & 0x400000000200ULL) fn_8003065C(u);
}

void fn_800275C4(Battle* b, u32 code, int n) {
    fn_80026208(b->log, 0x74);
    if (fn_80030CBC(&b->b)->data && fn_8011F2F0(&b->b, &b->a) == 0) {
        fn_80110D38(fn_80030CBC(&b->b));
    }
    if (b->b.x481) {
        fn_8002600C(b->log, 0x6c, 0);
        fn_80110D38(fn_80030CBC(&b->b));
    }
    if (b->f15ec & 0x8200) {
        fn_800300B4(&b->a);
        fn_800300B4(&b->b);
    }
    ranged(&b->a);
    ranged(&b->b);
    if (fn_8011B77C(b->a.u.x12c, lbl_804CA6A8) && fn_800300B4(&b->b)) fn_8002600C(b->log, 0xa, 0);
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA6A8) && fn_800300B4(&b->a)) fn_8002600C(b->log, 0x15, 0);
    if (fn_8011B77C(b->a.u.x12c, lbl_804CA63C) && fn_800300B4(&b->b)) fn_8002600C(b->log, 0x1b, 0);
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA63C) && fn_800300B4(&b->a)) fn_8002600C(b->log, 0x1c, 0);
    if (code == 0xf) {
        b->a.x480 = n ? 0 : fn_8002D430(&b->a);
    } else if (code == 0x15 && fn_8011B77C(b->a.u.x12c, lbl_804CA6F4)) {
        b->a.u.f108 |= 0x200;
        fn_8002600C(b->log, 0x40, 0);
    } else if (code == 0x41 && fn_8011B77C(b->a.u.x12c, lbl_804CA69C)) {
        b->a.u.f108 |= 0x400;
        fn_8002600C(b->log, 0x41, 0);
    } else if (code == 0x16 && fn_8011B77C(b->a.u.x12c, lbl_804CA6F0)) {
        FLAGS(&b->a.u) |= 0x80000000000ULL;
        FLAGS(&b->b.u) |= 0x80000000000ULL;
        fn_800300B4(&b->a);
        fn_800300B4(&b->b);
        fn_8002F20C(&b->a);
        fn_8002F20C(&b->b);
        FLAGS(&b->a.u) |= 0x10000000000ULL;
        FLAGS(&b->b.u) |= 0x10000000000ULL;
        fn_8002600C(b->log, 0x3d, 0);
    }
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA698) && fn_80030CBC(&b->b)->data) fn_8002600C(b->log, 0x3e, 0);
    flag4000(&b->a);
    flag4000(&b->b);
    if (b->f15e8 >= 2) {
        far1(&b->a);
        far1(&b->b);
    }
    if (b->f15e8 >= 2) {
        far2(&b->a);
        far2(&b->b);
    }
    if (b->a.x480) fn_8002600C(b->log, 0x3c, 0);
    fn_80026288(b->log);
}
}
