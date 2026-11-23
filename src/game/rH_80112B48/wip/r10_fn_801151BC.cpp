/* NOT MATCHING, not compiled. fn_801151BC: 5 words: v and the p8 temp swapped. fn_8011540C, the Job version, matches. */
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


void fn_801151BC(Map* m, Unit* u) {
    /*P*/
    u8* q;
    TileT* t;
    int i;
    int i0;
    int i2;
    int v;
    Map* w;
    int c;
    Job* j;
/*E*/
    if (u == 0) {
        for (i0 = 1; i0 < 0xc7; i0++) {
            m->costTbl[i0] = 1;
        }
        m->costTbl[0] = 0x7fff;
        m->unk2623D = 1;
        m->unk2623E = 0;
    } else {
        t = fn_8010B240(0);
        w = m;
        for (i = 0; i < 0xc7; i++) { 
            j = u->job; v = 0x7fff; q = t->p8; c = (s8)q[*((u8*)j + 0xf9) + 0x14]; if (c >= 0) { v = c; }
            t++; w->costTbl[0] = v; w = (Map*)((u8*)w + 2); }
        if (fn_8011B77C(u->skills, lbl_804CA50C)) {
            t = fn_8010B240(0);
            for (i2 = 0; i2 < 0xc7; i2++, t++) { if (t->p8[7] & 8) { m->costTbl[i2] = 1; } }
        }
        m->unk2623D = fn_8011B77C(u->skills, lbl_804CA500);
        m->unk2623E = fn_8011B77C(u->skills, lbl_804CA6A4);
    }
}
}
