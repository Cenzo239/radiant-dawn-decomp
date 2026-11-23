/* Height advantage of both combatants (names guessed). */
#include "game/rB_8002E1C4/battle.h"

struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};
extern MapS lbl_803EC898;
#define M (&lbl_803EC898)
extern const char lbl_80361338[];
extern "C" {
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
int fn_8002AAEC(BU* a, BU* d);

static inline u8 kA(Slot* s, BU* u) {
    if (s->data) return fn_801107C0(s->data, u);
    return 0;
}
static inline u8 kB(Slot* s, BU* u) {
    if (s->data) return fn_801107A0(s->data, u);
    return 0;
}

static inline s8 gx(BU* u) { return u->u.x102; }
static inline s8 gy(BU* u) { return u->u.y103; }
static inline f32 hdiff(s8 ax, s8 ay, s8 dx, s8 dy) {
    return -(fn_80114230(M, ax, ay) - fn_80114230(M, dx, dy));
}

void fn_8002ABE0(Battle* b, BU* a, BU* d) {
    int hit;
    void* m1;
    void* m2;
    Slot* s;
    Slot* s2;
    u8 k1;
    u8 k2;
    u8 k3;
    u8 k4;
    hit = 0;
    m1 = fn_80078D9C(-fn_801148D8(M, 7), lbl_80361338, 0);
    m2 = fn_80078D9C(-fn_801148D8(M, 9), lbl_80361338, 0);
    fn_80114944(M, 9, m2);
    s = fn_80030CBC(a);
    if (s->data && b->f15e8 > 1 && !(fn_801116B8(s)->flags & 0x5000)) {
        fn_801148CC(M, m1);
        fn_80114B44(M, 9, 0);
        k1 = kA(s, a);
        k2 = kB(s, a);
        fn_80115DEC(M, a->u.x102, a->u.y103, k2, k1);
        if (lbl_803EC898.xd18e[d->u.x102 + d->u.y103 * 64] && fn_8002AAEC(a, d)) {
            f32 v = hdiff(gx(a), gy(a), gx(d), gy(d));
            if (0.5 <= v) {
                a->s47e = 1;
            } else if (-0.5 >= v) {
                a->s47e = -1;
            } else {
                a->s47e = 0;
            }
            hit = 1;
        }
    }
    s2 = fn_80030CBC(d);
    if (s2->data && b->f15e8 > 1 && !(fn_801116B8(s2)->flags & 0x5000)) {
        fn_801148CC(M, m1);
        fn_80114B44(M, 9, 0);
        k3 = kA(s2, d);
        k4 = kB(s2, d);
        fn_80115DEC(M, d->u.x102, d->u.y103, k4, k3);
        if (lbl_803EC898.xd18e[a->u.x102 + a->u.y103 * 64] && fn_8002AAEC(d, a)) {
            f32 v = hdiff(gx(d), gy(d), gx(a), gy(a));
            if (0.5 <= v) {
                d->s47e = 1;
            } else if (-0.5 >= v) {
                d->s47e = -1;
            } else {
                d->s47e = 0;
            }
            hit = 1;
        }
    }
    if (hit) b->f15ec |= 0x1000000;
    fn_80114888(M, 7);
    fn_80114A44(M, 9, m2);
    fn_80078E24(m2);
    fn_80078E24(m1);
}
}
