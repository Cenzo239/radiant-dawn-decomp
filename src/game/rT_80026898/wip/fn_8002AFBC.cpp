/* fn_8002AFBC (r16): 6 of 188 words differ, only the map index x + y*64 at both sites: the original computes y<<6 into a new register before extsb x. Index spellings, locals, inline accessors and 2-D arrays did not fix it. */
/* Terrain bonus of both combatants (names guessed). */
#include "game/rB_8002E1C4/battle.h"

struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
    u8 pad1518e[0x15190 - (0xd18e + 0x2000)];
    s16* x15190;
    u16 atI(int x, int y) { return xd18e[x + y * 64]; }
    u16 atS(s8 x, s8 y) { return xd18e[x + y * 64]; }
    u16 atY(int y, int x) { return xd18e[x + y * 64]; }
    u16 atZ(s8 y, s8 x) { return xd18e[x + (y << 6)]; }
    u16 atW(s8 x, s8 y) { return xd18e[(y << 6) + x]; }
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
Slot* fn_80030CF4(BU* p);
ItemD* fn_801116B8(Slot* it);
int fn_801107C0(void* d, BU* u);
int fn_801107A0(void* d, BU* u);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
int fn_8028DB44(int v);

static inline u8 kA(Slot* s, BU* u) {
    if (s->data) return fn_801107C0(s->data, u);
    return 0;
}
static inline u8 kB(Slot* s, BU* u) {
    if (s->data) return fn_801107A0(s->data, u);
    return 0;
}
static inline u16 mvS(s8 x, s8 y) { return lbl_803EC898.xd18e[x + y * 64]; }
static inline u16 mv2(BU* d) { return ((u16(*)[64])lbl_803EC898.xd18e)[d->u.y103][d->u.x102]; }
static inline u16 mvI(int x, int y) { return lbl_803EC898.xd18e[x + y * 64]; }
static inline u16 mvY(s8 y, s8 x) { return lbl_803EC898.xd18e[x + y * 64]; }
static inline u16 mvC(const s8& x, const s8& y) { return lbl_803EC898.xd18e[x + y * 64]; }
static inline u8 wtype(Slot* s) {
    return s->data ? ((ItemD*)s->data)->x12 : 0x13;
}

static inline void terr(BU* a, BU* d, void* m1) {
    Slot* s = fn_80030CF4(a);
    if (s->data && wtype(s) == 3 && !(fn_801116B8(s)->flags & 0x4000)) {
        u8 k1, k2;
        fn_801148CC(M, m1);
        fn_80114B44(M, 9, 0);
        k1 = kA(s, a);
        k2 = kB(s, a);
        fn_80115DEC(M, a->u.x102, a->u.y103, k2, k1);
        if (lbl_803EC898.xd18e[d->u.x102 + d->u.y103 * 64]) {
            a->x478 += fn_8028DB44(lbl_803EC898.x15190[d->u.x102 + d->u.y103 * 64] - 2) * -30;
        }
    }
}

#pragma use_lmw_stmw on
void fn_8002AFBC(Battle* b, BU* a, BU* d) {
    void* m1;
    void* m2;
    d->x478 = 0;
    a->x478 = 0;
    m1 = fn_80078D9C(-fn_801148D8(M, 7), lbl_80361338, 0);
    m2 = fn_80078D9C(-fn_801148D8(M, 9), lbl_80361338, 0);
    fn_80114944(M, 9, m2);
    terr(a, d, m1);
    terr(d, a, m1);
    fn_80114888(M, 7);
    fn_80114A44(M, 9, m2);
    fn_80078E24(m2);
    fn_80078E24(m1);
}
#pragma use_lmw_stmw reset
}
