/* fn_8016EDE8: functionally equal (regs level per tools/check_regs.py; registers differ from the original).  */
/* fn_8016EDE8: 3 lines: the ter pointer temp should share r18 with v, and gets r16. */
#include "game/rQ_80163178/common.h"
extern "C" {
void fn_80165E18(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
int fn_8011EFC8(Unit*, Unit*);
int fn_8016CB60(Unit*, Inv*);
}
static inline BOOL HasW(Unit* u, Unit* v) {
    int i;
    BOOL any = 0;
    Inv* p = v->inv;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8016CB60(u, p)) {
            any = 1;
            break;
        }
    }
    return any;
}
extern "C" u32 fn_8016EDE8(Filter* f, Unit* u, s16* ox, s16* oy) {
/*P*/
    s16 best;
    s16 bx;
    s16 by;
    int y;
    int x;
    Unit* v;
/*E*/
    best = 0x7FFF;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v) && fn_8011EFC8(u, v) && HasW(u, v)) {
                    if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                        best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                        bx = x;
                        by = y;
                    }
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}
