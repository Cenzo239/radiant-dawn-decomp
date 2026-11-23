/* Count nearby units with a skill, 80124BC0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void fn_8010E41C(u8*, int);
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern u8 fn_8010E398(u8*, u8*);
extern void* lbl_804CA6B8;
#define HAS(u, s) fn_8011B77C((u)->skills, s)
#pragma use_lmw_stmw on
int fn_80124BC0(Unit* u, Unit** out) {
    Unit* v;
    Unit** w;
    u8 d;
    int n;
    int i;
    u8 tbl[0xb];
    n = 0;
    fn_8010E41C(tbl, 3);
    w = out;
    for (i = 1; i <= 0xfe; i++) {
        v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            d = ABS(u->x - v->x) + ABS(u->y - v->y);
            if (d <= 3 && d >= 1 && HAS(v, lbl_804CA6B8) && fn_8010E398(u->team, v->team) == 1) {
                if (out) {
                    *w = v;
                }
                w++;
                n++;
            }
        }
    }
    return n;
}
}
