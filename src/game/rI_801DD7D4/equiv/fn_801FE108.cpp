/* symcheck: r21 review, flag was an artefact. fn_801FE108: (a) stale store temporaries in r5-r10 at a `this`-only
   virtual call (vtable lbl_8038C294 slot 0xC = fn_801DD7D4, which reads r3 only); all stores equal. See
   docs/SCHED_REVIEW.md. */
/* fn_801FE108 (round 19): same body as fn_801EBF00 (its float literals come from another translation unit's pool). */
#pragma auto_inline off
#pragma inline_max_size(20000)
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
extern u8 lbl_8038CD64[], lbl_8038C294[], lbl_8038CD98[], lbl_8038CA88[];
void fn_801E2F40(void*, void*);
struct Col { u8 r, g, b, a; Col& operator=(const Col& o) { if (this != &o) { r = o.r; g = o.g; b = o.b; a = o.a; } return *this; } };
struct Eff { void* vt; int a4; int a8; u8 ac, ad; s16 ae, b0, b2; s16 a14; u8 p16[2]; f32 a18, a1c; Col c; f32 a24; };
class VE { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); };
struct SB { WF w; s16 a40, a42, a44; u8 a46; u8 p47; int a48, a4c, a50; Eff m1; Eff m2; };
static inline void effC(Eff* m, int a8) {
    m->vt = lbl_8038C294;
    m->a4 = 0;
    m->a8 = a8;
    m->ac = 1;
    m->ad = 1;
    m->a14 = 0;
    m->a18 = 1.0f;
    m->a1c = 1.0f;
    m->c.r = 0x80; m->c.g = 0x80; m->c.b = 0x80; m->c.a = 0xff;
    m->a24 = 0.0f;
}
static inline void effB(Eff* m, int a8) { effC(m, a8); ((VO0N*)m)->v0C(); }
static inline void effD(Eff* m) {
    m->vt = lbl_8038CD98;
    m->ad = 0;
    {
        Col k;
        k.r = 0x40; k.g = 0x40; k.b = 0x80; k.a = 0xff;
        m->c = k;
    }
}
static inline void effX(Eff* m, int a8) { effB(m, a8); effD(m); }
class VO { public: virtual int v08(); virtual int v0C(int, int); };
struct SO { WF w; u8 p[0xc]; SB* a4c; };
static inline void setP(Eff* m, s16 x, s16 y) { m->ae = x; m->b0 = y; m->b2 = 0; }
static inline void sbInit(SB* o, s16 y, s16 w, s16 h, s16 x, s16 z) {
    Eff* m1;
    wfInit(&o->w, x, y, x + w, y + h, w, h, z, 0x10);
    o->w.vt = lbl_8038CD64;
    o->a40 = 0;
    o->a42 = 0;
    o->a44 = 0;
    o->a46 = 1;
    o->a48 = 1;
    o->a4c = 0;
    o->a50 = 0;
    m1 = &o->m1; effX(m1, 2);
    { Eff* m = &o->m2; effX(m, 3); }
    o->w.vt = lbl_8038CA88;
    o->w.iy0 = 0x18;
    o->w.iy1 = (s16)(o->w.y1 - o->w.y0) - 0x18;
    {
        s16 cx = ((s16)(o->w.ix1 - o->w.ix0) + 1) >> 1;
        int r = ((VE*)&o->m2)->v24();
        s16 hh = (s16)r >> 1;
        setP(&o->m1, cx, -(hh + o->w.iy0));
        setP(&o->m2, cx, hh + (s16)(o->w.iy1 - o->w.iy0) + (s16)((s16)(o->w.y1 - o->w.y0) - o->w.iy1));
    }
}
static inline SB* newB(SO* s) {
    SB* o = (SB*)fn_80079150(0xa4);
    if (o != NULL) sbInit(o, 0, 8, s->w.iy1 - s->w.iy0, (s16)(s->w.ix1 - s->w.ix0) - 0xc, s->w.a26 - 5);
    return o;
}
static inline void setI(WF* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
void fn_801FE108(SO* s) {
    setI(&s->w, 4, 4, (s16)(s->w.x1 - s->w.x0) - 4, (s16)(s->w.y1 - s->w.y0) - 4);
    if (s->a4c != NULL) ((VO*)s)->v0C((int)s->a4c, 0);
    s->a4c = newB(s);
    fn_801E2F40(s, s->a4c);
}
}
