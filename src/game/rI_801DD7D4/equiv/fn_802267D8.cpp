/* fn_802267D8: functionally equal (check_regs: sched, 7 of 262 words differ). Corrected copy of wip/r15b/fn_802267D8.cpp
   (round 21 review): the callback pair {fn_80226BF0, *lbl_803CA870} is built in a temporary and copied to l->a80, so the
   word at lbl_803CA870 is read before the store to l->a80 as in the original (the wip version reads it after; harmless,
   a fresh heap object can't alias the static).
   symcheck: 1 block still flagged, an artefact: a ptmf copy temporary left in r4 at __ptmf_scall, whose target takes
   `this` only. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E495C(void*, void*, void*, int);
void fn_80226BF0(void* p, void* arg);
void fn_802236D8(void*);
void* fn_80223998(void*);
void* fn_8011A158(void*);
extern u8 lbl_8038FEB4[], lbl_8038FB60[];
extern u8 lbl_803CA870[];
extern int lbl_804CB7A8;
}
struct It;
typedef int (It::*PF)();
extern "C" {
extern PF lbl_803900D8;
It* fn_8010B22C(int);
}
struct It { u8 p[0x1f]; u8 a1f; };
struct Pred { PF f; void* o; };
struct XY { s16 x, y; };
struct Wy { void* vt; int rc; s16 id; s16 x, y; };
class LV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); };
struct L88 { WF w; int a40; LN l44; int a4c; int a50; u8 a54, a55; s16 a56; u8 p58[2]; s16 a5a, a5c, a5e, a60, a62; f32 a64; s16 a68; u8 p6a[0xa]; int a74; LN l78; void* a80; void* a84; };
struct WQ2 { WF w; void* a40; };
struct S7 { u8 p[0x54]; L88* a54; WQ2* a58; };
static inline void mv3(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline L88* newL(void) {
    L88* o = (L88*)fn_80079150(0x88);
    if (o != NULL) {
        gInit((G40*)o, 0x191, 0x48, 0x299, 0x108, 0x108, 0xc0, 0x1e0, 0x10);
        o->w.vt = lbl_8038FEB4;
        o->a4c = 0;
        o->a50 = 0;
        o->a54 = 1;
        o->a55 = 0;
        o->a56 = 0;
        o->a5a = -0x8000;
        o->a5c = -0x8000;
        o->a5e = 0;
        o->a60 = 1;
        o->a62 = 0x21;
        o->a64 = 0.0f;
        o->a68 = 0;
        o->a74 = 0;
        {LN* l = &o->l78; l->next = l; l->prev = l;}
        o->a80 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline WQ2* newV(void) {
    WQ2* o = (WQ2*)fn_80079150(0x44);
    if (o != NULL) {
        wfInit(&o->w, 0x198, 0x13c, 0x28e, 0x19c, 0xf6, 0x60, 0x1e0, 0x10);
        o->w.vt = lbl_8038FB60;
        o->a40 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void fill(LV* l, Pred p);
static inline void fill2(LV* l, Pred p) { fill(l, p); }
struct Pred2 { PF f; void* o; Pred2(PF a, void* b) : f(a), o(b) {} };
static inline int call2(Pred2 p, It* it) { return (it->*p.f)(); }
static inline void fillB(LV* l, Pred2 p) {
    for (int i = 0; i < lbl_804CB7A8; i++) {
        It* it = fn_8010B22C(i);
        if (it->a1f != 0) { if (call2(p, it)) l->v30(it); }
    }
}
static inline void fillB2(LV* l, Pred2 p) { fillB(l, p); }
static inline Pred mkp(PF a, void* b) { Pred p; p.f = a; p.o = b; return p; }
static inline int call(Pred p, It* it) { return (it->*p.f)(); }
static inline int callR(const Pred& p, It* it) { return (it->*p.f)(); }
static inline void fill(LV* l, Pred p) {
    for (int i = 0; i < lbl_804CB7A8; i++) {
        It* it = fn_8010B22C(i);
        if (it->a1f != 0) { if (call(p, it)) l->v30(it); }
    }
}

extern "C" void fn_802267D8(S7* s) {
    {
        Wy* a = (Wy*)fn_801E5640(s, 0x81, 0);
        if (a != NULL && a->y != -0x24) mv3(s, a, a->x, -0x24, 0);
    }
    {
        L88* r = newL();
        s->a54 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a54->w.id = 0x85;
    s->a54->w.a28 = 8;
    { L88* l = s->a54; struct P2 { void* f; void* d; }; P2 t; t.f = (void*)fn_80226BF0; t.d = *(void**)lbl_803CA870; *(P2*)&l->a80 = t; }
    s->a54->a54 = 0;
    s->a54->a50 = *(int*)lbl_803CA870;
    fill((LV*)s->a54, mkp(lbl_803900D8, *(void**)lbl_803CA870));

    fn_802236D8(s->a54);
    fn_801E5448(s, s->a54);
    {
        WQ2* r = newV();
        s->a58 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a58->w.id = 0x88;
    s->a58->w.a28 = 8;
    s->a58->a40 = fn_80223998(s->a54) != NULL ? fn_8011A158(fn_80223998(s->a54)) : NULL;
    fn_801E5448(s, s->a58);
}
