/* Finds a unit next to the defender that steps in to protect it (names guessed). */
#define lbl_803C8E80 lbl_unused
#include "game/rB_8002E1C4/battle.h"
#undef lbl_803C8E80

struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
};
struct Roll { u8 pad[0xa3]; u8 xa3; };
extern MapS lbl_803EC898;
#define M (&lbl_803EC898)
extern Roll lbl_803C8DA0;
extern u8* lbl_804CB810;
extern void* lbl_804CA590;
extern void* lbl_804CA6DC;
extern "C" {
int fn_8011799C(MapS* m, s8 x, s8 y);
int fn_8011B77C(void* list, void* key);
Unit* fn_80127B68(Unit* u);
Unit* fn_8012E3A4(Unit* u);
f32 fn_80127868(Unit* u);
Rec7 fn_801278B8(Unit* u, f32 bio);
int fn_8012E9B4(Unit* a, Unit* b);
u8 fn_8012E8BC(Unit* a, s8 k);
int fn_80089D68(int n);
extern Battle lbl_803C8E80;

static inline Unit* orig(BU* c) { return c->u.u3f0; }
static inline int dirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    }
    return 0x40;
}
static inline int dirX(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int dirY(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
static inline u8 cell(s8 x, s8 y) {
    return lbl_803EC898.grid[x + y * 64];
}
static inline Unit* unitAt(int id) {
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
    Unit* p;
    int x;
    int y;
    int i;
    int nx;
    int ny;
    Unit* u;
    int v;
    p = orig(&b->b);
    if (p == 0) return 0;
    x = p->x102;
    y = p->y103;
    for (i = 0; i < 4; i++) {
        int d = dirBit(i);
        nx = x + dirX(d);
        ny = y + dirY(d);
        if (fn_8011799C(M, nx, ny)) {
            u8 id = cell(nx, ny);
            if (id) {
                u = unitAt(id);
                if (u->f4[8] == p->f4[8]) {
                    if (fn_8011B77C(u->x12c, lbl_804CA590) && p == fn_80127B68(u)) return u;
                    if (fn_8012E3A4(p) == u && fn_8011B77C(u->x12c, lbl_804CA6DC)) {
                        f32 bioA = fn_80127868(u);
                        Rec7 r = fn_801278B8(u, bioA);
                        v = r.f;
                        switch (fn_8012E8BC(p, fn_8012E9B4(p, u))) {
                        case 1: v += 15; break;
                        case 2: v += 20; break;
                        case 3: v += 25; break;
                        }
                        if (v < 0) v = 0;
                        if (rollP(v)) return u;
                    }
                }
            }
        }
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
