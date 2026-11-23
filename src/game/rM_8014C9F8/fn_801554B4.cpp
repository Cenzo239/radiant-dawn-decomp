/* fn_801554B4: AI, is any enemy within item range reachable from a free tile (names guessed). */
#include "game/rM_8014C9F8/ai.h"
extern "C" {
extern int fn_80109384(void*);
extern Inv* fn_8012759C(Unit*);
extern int fn_801658E4(Unit*, int, int);

static inline int G(Unit* u) { return (s8)fn_8012408C(u); }
#pragma use_lmw_stmw on
static inline int Dist(Unit* u, Unit* v) { int r = fn_8028DB44(u->y - v->y); int d = fn_8028DB44(u->x - v->x); return d + r; }
static inline void Dist2(Unit* u, Unit* v, int& d) { int r = fn_8028DB44(u->y - v->y); d = fn_8028DB44(u->x - v->x); d += r; }
BOOL fn_801554B4(Unit* u) {
    /*P*/
    int d;
    int i;
    Unit* uu;
    Inv* p;
    Unit* v;
    int r;
    int y;
    int x;
/*E*/
    u8 tbl[0xC];
    if (fn_80109384((u8*)u + 0x110) || (u->flags10C & 0x9D)) {
        return 0;
    }
    fn_80165F94(u, 6, -1);
    p = (Inv*)fn_8012759C(u);
    if (p == NULL || p->item == NULL) {
        return 0;
    }
    fn_8010E41C(tbl, 1);
    for (i = 1; i <= 0xFE; i++) {
        v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            d = Dist(u, v);
            if (p->item != NULL) {
                r = (u8)fn_801107C0(p->item, u);
            } else {
                r = 0;
            }
            int g = G(u);
            if (d <= g + r && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v) && fn_8011F1A8(u, v)) {
                int b;
                if (p->item != NULL) {
                    r = (u8)fn_801107C0(p->item, u);
                } else {
                    r = 0;
                }
                if (p->item != NULL) {
                    b = (u8)fn_801107A0(p->item, u);
                } else {
                    b = 0;
                }
                fn_801663E0(v->x, v->y, b, r, 7);
                for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
                    for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
                        if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < 0) continue;
                        if (lbl_803EC898.b5S[(s8)x + (s8)y * 0x40]) continue;
                        if (fn_801658E4(u, (s8)x, (s8)y)) continue;
                        if (lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0) continue;
                        {
                            u32 t = lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40];
                            if (t && t != u->padFC[0]) continue;
                        }
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
}
