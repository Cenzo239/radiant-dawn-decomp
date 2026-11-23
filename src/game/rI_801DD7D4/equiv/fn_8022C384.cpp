/* symcheck: r21 review, flag was an artefact. fn_8022C384: (a) 3 blocks: stale store temporaries in r4-r10 at
   three `this`-only virtual calls (fn_801DD7D4, fn_8022C244, v34); all stores and their order equal. See
   docs/SCHED_REVIEW.md. */
/* fn_8022C384: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
#pragma inline_max_size(20000)
#pragma inline_depth(16)
extern "C" {
extern u8 lbl_8038CD98[], lbl_8038CD64[], lbl_8038CA88[], lbl_80390468[];
void* fn_8022A5F8(void*, int, s16, s16, s16);
struct Col { u8 r, g, b, a; Col() {} Col(u8 x, u8 y, u8 z, u8 w) { r = x; g = y; b = z; a = w; } Col& operator=(const Col& o) { if (this != &o) { r = o.r; g = o.g; b = o.b; a = o.a; } return *this; } };
struct Ea { void* vt; int a4; int a8; u8 ac, ad; s16 ax, ay, az; s16 a14; u8 p16[2]; f32 a18, a1c; Col c; f32 a24; };
static inline void eaBase(Ea* m, int d) {
    m->vt = lbl_8038C294;
    m->a4 = 0;
    m->a8 = d;
    m->ac = 1;
    m->ad = 1;
    m->a14 = 0;
    m->a18 = 1.0f;
    m->a1c = 1.0f;
    m->c.r = 0x80; m->c.g = 0x80; m->c.b = 0x80; m->c.a = 0xff;
    m->a24 = 0.0f;
    ((VO0N*)m)->v0C();
}
static inline void eaArrow(Ea* m, int d, Col& k) {
    eaBase(m, d);
    m->vt = lbl_8038CD98;
    m->ad = 0;
    k.r = 0x40; k.g = 0x40; k.b = 0x80; k.a = 0xff;
    m->c = k;
}
struct SB { WF w; s16 a40, a42, a44; u8 a46; u8 p47; int a48, a4c, a50; Ea e0; Ea e1; };
struct T80 { WF w; u8 p40[0x34]; s16 a74, a76, a78; u8 p7a[2]; int a7c; };
struct Sc2 { WF w; u8 p40[0x14]; s16 a54; u8 p56[0x1e]; WF* a74; WF* a78; WF* a7c; };
class VE { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); };
class VS { public: virtual int v08(); virtual void v0C(void*, int); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); };
static inline void setR(WF* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
static inline void eaPos(Ea* m, s16 x, s16 y) { m->ax = x; m->ay = y; m->az = 0; }
static inline void sbInit(SB* o, int h, int x0, int a26) {
/*P*/
    Col k1;
    Col k0;
    Ea* m0;
    Ea* m1;
    int t;
    int h2;
/*E*/
        wfInit(&o->w, x0, 0, (s16)x0 + 8, h, 8, h, a26, 0x10);
        o->w.vt = lbl_8038CD64;
        o->a40 = 0;
        o->a42 = 0;
        o->a44 = 0;
        o->a46 = 1;
        o->a48 = 1;
        o->a4c = 0;
        o->a50 = 0;
        m0 = &o->e0; eaArrow(m0, 2, k0);
        m1 = &o->e1; eaArrow(m1, 3, k1);
        o->w.vt = lbl_8038CA88;
        o->w.iy0 = 0x18;
        o->w.iy1 = (s16)(o->w.y1 - o->w.y0) - 0x18;
        t = ((s16)(o->w.ix1 - o->w.ix0) + 1) >> 1;
        h2 = (s16)((VE*)&o->e1)->v24() >> 1;
        eaPos(&o->e0, t, -(h2 + o->w.iy0));
        eaPos(&o->e1, t, h2 + (s16)(o->w.iy1 - o->w.iy0) + (s16)((s16)(o->w.y1 - o->w.y0) - o->w.iy1));
}
static inline SB* newSB(Sc2* s) {
    SB* o = (SB*)fn_80079150(0xa4);
    if (o != NULL) {
        sbInit(o, s->w.iy1 - s->w.iy0, (s16)(s->w.ix1 - s->w.ix0) - 0x10, s->w.a26 - 5);
    }
    return o;
}
static inline T80* newT(Sc2* s) {
    T80* o = (T80*)fn_80079150(0x80);
    if (o != NULL) {
        wfInit(&o->w, 0x62, -0x1c, 0x166, 4, 0x104, 0x20, s->w.a26 - 5, 0x10);
        o->w.vt = lbl_80390468;
        o->a74 = 0;
        o->a76 = -0x8000;
        o->a78 = -0x8000;
        o->a7c = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void at(WF* w, int x, int y) {
    w->x1 = x + (s16)(w->x1 - w->x0);
    w->x0 = x;
    w->y1 = y + (s16)(w->y1 - w->y0);
    w->y0 = y;
}
static inline void addT(Sc2* s, int id, int a28, int sel, f32 f) {
    {
        WF* r = (WF*)fn_80079150(0x60);
        if (r != NULL) r = (WF*)fn_8022A5F8(r, 0, 0, 0, s->w.a26 - 4);
        s->a7c = r;
        if (r != NULL) r->rc++;
    }
    s->a7c->id = id;
    s->a7c->a28 = a28;
    {
        WF* w = s->a7c;
        at(w, ((s16)(s->w.ix1 - s->w.ix0) - (s16)(w->x1 - w->x0)) >> 1, ((s16)(s->w.iy1 - s->w.iy0) - (s16)(w->y1 - w->y0)) >> 1);
    }
    if (sel == (s16)((VS*)s)->v34()) fn_801E2F40(s, s->a7c);
    else s->a7c->sy = f;
}
void fn_8022C384(Sc2* s) {
    setR(&s->w, 4, 4, (s16)(s->w.x1 - s->w.x0) - 4, (s16)(s->w.y1 - s->w.y0) - 4);
    s->w.tx = 0;
    s->w.ty = 0;
    s->a54 = 0x1c;
    if (s->a74 != NULL) ((VS*)s)->v0C(s->a74, 0);
    {
        WF* o = (WF*)newSB(s);
        s->a74 = o;
        fn_801E2F40(s, o);
    }
    if (s->a78 != NULL) ((VS*)s)->v0C(s->a78, 0);
    {
        WF* t = (WF*)newT(s);
        s->a78 = t;
        t->id = 0x80;
        fn_801E2F40(s, s->a78);
    }
    {
        f32 f = 0.0f;
        int i;
        int id;
        int k;
        id = 0x81;
        k = 4;
        for (i = 0; i < 1; i++, id++) {
            addT(s, id, k, i, f);
        }
    }
}
}
