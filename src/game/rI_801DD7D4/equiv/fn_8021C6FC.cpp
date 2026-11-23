/* fn_8021C6FC (0x358): per-frame update of a 5-card selector. Eases each card's alpha (sz) and scale (sx)
 * towards 1.0/1.0 for the selected card (or all when no selection is active) and towards 0.7/0.84 for the
 * others, by half the remaining distance per frame, then forwards the update to all children.
 * Class `regs` (round 20): same instructions, order and references; only saved GPRs differ (the counter
 * is r31 in the original, r27 here). Field names are guesses. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
f32 fn_801E3300(void*);
f32 fn_801E3468(void*);
typedef void (RObj::*MF)(int);
struct FnT { MF f; int arg; };
extern MF lbl_8038F7E0;
struct N3 { u8 p[0x2c]; f32 sx, sy, sz; u8 p38[4]; N3* parent; };
class SO { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*);
    u8 p4[0x3c]; int a40; LNode* a44; LNode* a48; N3* a4c[5]; u8 a60; u8 p61[9]; s16 a6a;
};
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    N3* p; N3* q; N3* r; N3* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
void fn_8021C6FC(SO* o, void* c) {
    N3* w; int i;
    ((VO0N*)o)->v3C();
    o->v18(c);
    for (i = 0; i < 5; i++) {
        w = o->a4c[i];
        if (w == NULL) continue;
        if (!o->a60 || i == o->a6a) {
            { f32 e, d, b, a; CHAIN(w, sz, fn_801E3468, a, b, d, e);
            if (a < 1.0f) {
                a = 0.5f * (1.0f - a) + a;
                if (a > 1.0f) a = 1.0f;
                w->sz = a;
            } }
            { f32 a, b, d, e; CHAIN(w, sx, fn_801E3300, e, d, b, a);
            if (e < 1.0f) {
                e = 0.5f * (1.0f - e) + e;
                if (e > 1.0f) e = 1.0f;
                w->sx = e;
            } }
        } else {
            { f32 a, b, d, e; CHAIN(w, sz, fn_801E3468, e, d, b, a);
            if (0.7f < e) {
                e = e - 0.5f * (e - 0.7f);
                if (e < 0.7f) e = 0.7f;
                w->sz = e;
            } }
            { f32 a, b, d, e; CHAIN(w, sx, fn_801E3300, e, d, b, a);
            if (0.84f < e) {
                e = e - 0.5f * (e - 0.84f);
                if (e < 0.84f) e = 0.84f;
                w->sx = e;
            } }
        }
    }
    {
        FnT g;
        LNode* sent = (LNode*)&o->a44;
        g.f = lbl_8038F7E0;
        g.arg = (int)c;
        forEach(o->a48, sent, g);
    }
}
}
