/* AI: attack search with a named item, fn_80155090. */
#include "game/rM_8014C9F8/ai.h"
struct Obj { u8* p; u8 d[0x24]; };
extern "C" {
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_80110BFC(void*, void*);
extern int fn_8015797C(Unit*, AiBest*, void*);

static inline int G(Unit* u) { return (s8)fn_8012408C(u); }
#pragma use_lmw_stmw on
u8 fn_80155090(Filter* f, void* arg, void* itm, int act) {
    
    Unit* v;
    Unit* u;
    int i;
    int r;
    int d;
    u8 r0;
    
    Map* m = &lbl_803EC898;
    AiBest best;
    AiBest cur;
    Obj o;
    u8 tbl[0xC];
    u = lbl_803CA870.unit;
    fn_800453B4(&lbl_803CA870, act);
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.t = NULL;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    memset(&cur, 0, 0x10);
    fn_80111B34(&o);
    fn_80110BFC(&o, itm);
    cur.item = *(u16*)(o.p + 0xE);
    fn_8010E41C(tbl, 1);
    for (i = 1; i <= 0xFE; i++) {
        v = UnitGet(i);
        if (v->person && tbl[v->team[8]] && f->check(v)) {
            r = fn_8028DB44(u->y - v->y);
            d = fn_8028DB44(u->x - v->x);
            d += r;
            if (o.p != NULL) {
                r = (u8)fn_801107C0(o.p, u);
            } else {
                r = 0;
            }
            int g = G(u);
            if (d <= g + r && !(v->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, v) && fn_8011F1A8(u, v)) {
                int b;
                if (o.p != NULL) {
                    r = (u8)fn_801107C0(o.p, u);
                } else {
                    r = 0;
                }
                if (o.p != NULL) {
                    b = (u8)fn_801107A0(o.p, u);
                } else {
                    b = 0;
                }
                fn_801663E0(v->x, v->y, b, r, 7);
                cur.t = v;
                if (fn_8015797C(u, &cur, arg)) {
                    if (fn_8016D070()) {
                        if (*(u32*)(fn_80158C98() + 0x14) & 0x100) {
                            if (!(cur.fl & 8)) goto P;
                            continue;
                        }
                    } else if (fn_8016D090() && (cur.fl & 8)) {
                        continue;
                    }
                    P:
                    if (cur.score > best.score) {
                        best = cur;
                    }
                }
            }
        }
    }
    if (best.t != NULL) {
        fn_80160610(lbl_803CA870.action, (s8)best.x, (s8)best.y, best.t, (s8)*(u8*)&best.t->x, best.t->y, (s8)best.item, 0, 0);
        u->b3BC |= best.fl;
        u->h3BE = best.score;
    }
    r0 = lbl_804183F0.done;
    fn_80111C24(&o, -1);
    return r0;
}
}
