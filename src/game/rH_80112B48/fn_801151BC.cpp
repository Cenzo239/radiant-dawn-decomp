/* fn_801151BC (0x250): exact (round m8). Terrain costs for a unit; fn_8011540C is the Job version.
 * The cost byte is read through an accessor that the source evaluates twice (`Cost(..) >= 0 ? Cost(..) : 0x7fff`):
 * the table pointer then has two uses, is loaded before the default and gets r6 (default r5) as in the original.
 * A single read (`c = ..; if (c >= 0) v = c;`) is the same code with those two registers exchanged. */
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

/* cost of terrain t for a job's movement type; negative = impassable */
static inline s8 Cost(TileT* t, Job* j) { return t->p8[*((u8*)j + 0xf9) + 0x14]; }

void fn_801151BC(Map* m, Unit* u) {
    TileT* t;
    int i;
    int i0;
    int i2;
    if (u == 0) {
        for (i0 = 1; i0 < 0xc7; i0++) {
            m->costTbl[i0] = 1;
        }
        m->costTbl[0] = 0x7fff;
        m->unk2623D = 1;
        m->unk2623E = 0;
    } else {
        t = fn_8010B240(0);
        for (i = 0; i < 0xc7; i++, t++) {
            m->costTbl[i] = Cost(t, u->job) >= 0 ? Cost(t, u->job) : 0x7fff;
        }
        if (fn_8011B77C(u->skills, lbl_804CA50C)) {
            t = fn_8010B240(0);
            for (i2 = 0; i2 < 0xc7; i2++, t++) { if (t->p8[7] & 8) { m->costTbl[i2] = 1; } }
        }
        m->unk2623D = fn_8011B77C(u->skills, lbl_804CA500);
        m->unk2623E = fn_8011B77C(u->skills, lbl_804CA6A4);
    }
}
}
