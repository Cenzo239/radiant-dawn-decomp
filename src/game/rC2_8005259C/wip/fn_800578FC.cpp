/* NEAR MISS: 4 of 80 words (fn_80057B7C is the mirror image). Only the two y loads swap registers
 * (want p->y in r4 and t->y in r5). fn_800577BC and fn_80057A3C, the same search on the other axis, match. */
#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on
typedef struct Tile { s8 x; s8 y; u8 pad2[0x12]; struct Tile* n14; struct Tile* n18; struct Tile* n1c; struct Tile* n20; struct Tile* n24; } Tile;
extern "C" Tile* fn_800CFD18(Word* w, int i);
static inline int iabs(int v) { return v < 0 ? -v : v; }
extern "C" int fn_800578FC(Tile* t) {
        s16 best;
    Tile* b;
    int i;
    s8 oy;
    Tile* p;
    s8 ty;
    int a2;
    int a;
    s16 d;

    best = 0x7fff;
    b = 0;
    for (i = 0; i < lbl_803E7320.i0; i++) {
        p = fn_800CFD18(&lbl_803E7320, i);
        if (t == p) continue;
        if (t->x >= p->x) continue;
        oy = p->y;
        ty = t->y;
        a2 = ty - oy;
        a = t->x - p->x;

        a2 = iabs(a2); a = iabs(a); d = a + a2;
        if (best < d) continue;
        if (b == 0 || best != d || (b->x == p->x ? b->y < oy : p->x < b->x)) {
            best = d;
            b = p;
        }
    }
    t->n18 = b ? b : t;
    return b != 0;
}
