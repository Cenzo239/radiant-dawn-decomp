/* EQUIVALENT (register-only, round 19): fn_80112CD4 at regs level; r14 wip with the second loop's increments in original order (e2++, i++). */
/* Support-pair bonus: sum over adjacent active pairs, 80112CD4. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
struct PairEnt { void* a; void* b; u8 c; s8 d; };
extern PairEnt* lbl_804CB7E4;
extern PairEnt lbl_803EC418[];
extern int lbl_804CB800;
extern u32 lbl_804CB700;
extern Map lbl_803EC898;
extern Unit* fn_8012CECC(void*);
extern u8 fn_80126F34(Unit*, Unit*);
extern int fn_80116DB8(Map*, int, int, int, int);
#define OK(R, m, z, a, b, s) \
    if (a == 0 || b == 0) { R = 0; } \
    else if (fn_80126F34(a, b) != 1) { R = 0; } \
    else { \
    s = m->unk2623D != 0; \
    m->unk2623D = z; \
    if (!fn_80116DB8(m, a->x, a->y, b->x, b->y)) { R = 0; } \
    else { \
    m->unk2623D = s; \
    R = a->team == b->team; } }
#pragma push
#pragma use_lmw_stmw on
s8 fn_80112CD4(Unit* u, int k) {
    /*P*/
    Map* m1;
    int z2;
    int z1;
    Map* m2;
    Unit* a;
    Unit* b2;
    Unit* b;
    Unit* a2;
    PairEnt* e;
    PairEnt* e2;
    int n;
    int i;
    BOOL s;
    BOOL s2;
    /*E*/
    n = 0;
    if (lbl_804CB700 & 0x20000) {
        return 0;
    }
    m1 = &lbl_803EC898;
    z1 = 0;
    for (e = lbl_804CB7E4; e->a; e++) {
        if (e->c == 1 && (u->person == e->a || u->person == e->b) && k == 0) {
            b = fn_8012CECC(e->b);
            a = fn_8012CECC(e->a);
            {
            BOOL R;
            OK(R, m1, z1, a, b, s)
            if (R) {
                n += e->d;
            }
            }
        }
    }
    e2 = lbl_803EC418;
    m2 = &lbl_803EC898;
    z2 = 0;
    for (i = 0; i < lbl_804CB800; e2++, i++) {
        if (e2->c == 1 && (u->person == e2->a || u->person == e2->b) && k == 0) {
            b2 = fn_8012CECC(e2->b);
            a2 = fn_8012CECC(e2->a);
            {
            BOOL R;
            OK(R, m2, z2, a2, b2, s2)
            if (R) {
                n += e2->d;
            }
            }
        }
    }
    return n;
}
#pragma pop
}
