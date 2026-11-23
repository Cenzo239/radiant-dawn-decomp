/* symcheck: r21 review, flag was an artefact. fn_8023DCC0: (a) `...bss.0` is lbl_80425478; stale r5-r7 before
   fn_8023B5B0 (reads r3, r4). See docs/SCHED_REVIEW.md. */
/* fn_8023DCC0: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* fn_8023DCC0: find a loaded archive/file entry by name (hash, then string compare) in both lists. */
#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern u8 lbl_80390C58[];
FE* fn_802BC2A4(void*, FE*);
void fn_8023B5B0(FE*, const char*);
int fn_80291188(const char*, const char*);
}
static inline void feInit(FE* e) {
    e->flags = 0;
    e->vt = lbl_80390C58;
    e->name[0] = 0;
    e->a4b = -1;
    e->hash = 0;
    e->rc = 0;
    e->a56 = 2;
    e->parent = 0;
    e->data = 0;
    e->size = 0;
    e->pos = 0;
    e->a4 = 0;
    e->a8 = 0;
}
struct Key { FE e; Key() { feInit(&e); } ~Key() { feInit(&e); } };
extern "C" FE* fn_8023DCC0(const char* name) {
    FE* f = NULL;
    Key k;
    VO0N* l;
    FE* a;
    fn_8023B5B0(&k.e, name);
    l = (VO0N*)sLock;
    l->v08();
    for (a = fn_802BC2A4(sA, NULL); a != NULL; a = fn_802BC2A4(sA, a)) {
        if (k.e.hash == a->hash && fn_80291188(k.e.name, a->name) == 0) { f = a; goto done; }
    }
    for (a = fn_802BC2A4(sB, NULL); a != NULL; a = fn_802BC2A4(sB, a)) {
        if (k.e.hash == a->hash && fn_80291188(k.e.name, a->name) == 0) { f = a; goto done; }
    }
done:
    l->v10();
    return f;
}
