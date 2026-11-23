#include "game/rQ_80163178/common.h"
extern "C" {
void fn_80165E18(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
int fn_8011EDC4(Unit*, Unit*);
}
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
extern "C" u32 fn_8016E9A8(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best;
    s16 bx;
    s16 by;
    int y;
    int x;
    Unit* v;
    best = 0x7FFF;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v) && !SameT(u, v, 1) && fn_8011EDC4(u, v) && !(v->flags10C & 6) && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v)) {
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
extern "C" u32 fn_8016EBD8(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best;
    s16 bx;
    s16 by;
    int y;
    int x;
    Unit* v;
    best = 0x7FFF;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v) && fn_8011EDC4(u, v) && !(v->flags10C & 6) && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v)) {
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
