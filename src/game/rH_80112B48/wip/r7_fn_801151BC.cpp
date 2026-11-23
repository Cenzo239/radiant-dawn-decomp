/* NOT MATCHING, not compiled. fn_801151BC: 21 words, first fill loop counter wants r8; v and table pointer swapped. fn_8011540C is the same with a Job parameter. */
/* Map cost tables and flood fill, 80113428, 8011398C, 801151BC, 8011540C, 80115AC8, 80115DEC. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {
extern void* lbl_804CA50C;
extern void* lbl_804CA500;
extern void* lbl_804CA6A4;
extern int fn_8011B77C(void*, void*);
struct TileT {
    u8 pad0[8];
    u8* p8;
    u8 padC[4];
};
extern TileT* fn_8010B240(int);

static inline void CostDefault(Map* m) {
    int i;
    for (i = 1; i < 0xc7; i++) {
        m->costTbl[i] = 1;
    }
    m->costTbl[0] = 0x7fff;
    m->unk2623D = 1;
    m->unk2623E = 0;
}

static inline int TC(TileT* t, Job* j) { int v = 0x7fff; s8 c = t->p8[*((u8*)j + 0xf9) + 0x14]; if (c >= 0) { v = c; } return v; }
static inline s8 TC0(TileT* t, Job* j) { return t->p8[*((u8*)j + 0xf9) + 0x14]; }
static inline u16 TC2(s8 c) { return c >= 0 ? c : 0x7fff; }
static inline void TC3(Map* m, Job* j, TileT* t) { int i; for (i = 0; i < 0xc7; i++) { int v = 0x7fff; int c = TC0(t, j); if (c >= 0) { v = c; } t++; m->costTbl[i] = v; } }
void fn_801151BC(Map* m, Unit* u) {
    if (u == 0) {
        CostDefault(m);
    } else {
        TileT* t = fn_8010B240(0);
        int i;
for (i = 0; i < 0xc7; i++) { int v = TC(t, u->job); t++; m->costTbl[i] = v; }        if (fn_8011B77C(u->skills, lbl_804CA50C)) {
            t = fn_8010B240(0);
for (i = 0; i < 0xc7; i++, t++) { if (t->p8[7] & 8) { m->costTbl[i] = 1; } }
        }
        m->unk2623D = fn_8011B77C(u->skills, lbl_804CA500);
        m->unk2623E = fn_8011B77C(u->skills, lbl_804CA6A4);
    }
}

}
