/* fn_8012152C (0x1D4): `sched` (round 21, tools/check_regs.py; 117 of 117 instructions). symcheck --anon:
 * 22 blocks, 0 differ. Moved lines (dd.py): only in the entry block: `addi r30` of the map address and
 * `mr r20,r3` swap, and the address arithmetic of the "lift the unit" byte (extsb/slwi/add, li 0, li 6, mr r3)
 * is scheduled in another order with the sum as m + idx instead of idx + m. check_func.py's one "wrong
 * reference" (+0x1E) is the artefact of that one-slot shift.
 * Finds the cheapest free tile near (*ox, *oy) for unit `u` (names guessed): with the unit lifted off the map,
 * rebuilds the movement grid from (*ox, *oy) (range 0x40, movement type from the pooled name at
 * lbl_80369010+0x51), then scans the playable area for the reachable tile with the lowest cost that is not
 * marked in g5, not refused by fn_801658E4, unoccupied and passable (fn_80115CD8 <= 30000), and writes it back
 * to *ox, *oy. Self-contained version of wip/r7_fn_8012152C.txt.
 */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern Map lbl_803EC898;
extern char lbl_80369010[];
extern void* fn_8010B200(void*);
extern void fn_80114888(Map*, int);
extern void fn_801151BC(Map*, Unit*);
extern s16 fn_80115CD8(Map*, int, int);
extern void fn_8011567C(Map*, int);
extern void fn_8011540C(Map*, void*);
extern void fn_80115764(Map*, int, int, int);
extern int fn_801658E4(Unit*, int, int);
void fn_8012152C(Unit* u, s8* ox, s8* oy);
}
static inline void Sc(Map* m, Unit* u, s8* ox, s8* oy) {
    u16 best;
    u8 keep = m->ter[0][u->x + u->y * 0x40];
    int y;
    m->ter[0][u->x + u->y * 0x40] = 0;
    fn_80114888(m, 6);
    fn_8011567C(m, 0);
    fn_8011540C(m, fn_8010B200(lbl_80369010 + 0x51));
    fn_80115764(m, *ox, *oy, 0x40);
    fn_801151BC(m, u);
    best = 9999;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        int x;
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (((s16*)m->cur)[(s8)x + (s8)y * 0x40] >= 0) {
                Map* q = (Map*)((u8*)m + (s8)y * 0x40 + (s8)x);
                if (*(s8*)q->g5 == 0 && fn_801658E4(u, (s8)x, (s8)y) == 0 && q->ter[0][0] == 0) {
                    if (fn_80115CD8(m, (s8)x, (s8)y) <= 30000) {
                        s16 c = ((s16*)m->cur)[(s8)x + (s8)y * 0x40];
                        if (best > (u16)c) {
                            *ox = x;
                            best = c;
                            *oy = y;
                        }
                    }
                }
            }
        }
    }
    m->ter[0][u->x + u->y * 0x40] = keep;
}
extern "C" void fn_8012152C(Unit* u, s8* ox, s8* oy) {
    Sc(&lbl_803EC898, u, ox, oy);
}
