/* WIP r16: fn_802414C4, 17 of 314 words; only volatile registers of the scroll bar constructor constants (0x18, 8, a26-5) differ. */
#include "game/rI_801DD7D4/fn_wf.h"
/* Talk list window: sets its inner rectangle, then rebuilds the title strip (+0x4C) and the
   scroll bar (+0x50) with its two arrow effects. */
extern "C" {
extern u8 lbl_80390F54[], lbl_8038CD64[], lbl_8038CD98[], lbl_8038CA88[];
}
class WCh {
public:
    virtual int v08();
    virtual int remove(void*, int); /* +0x0C */
};
struct Col {
    u8 r, g, b, a;
    Col() {}
    Col& operator=(const Col& o) {
        if (this != &o) {
            r = o.r;
            g = o.g;
            b = o.b;
            a = o.a;
        }
        return *this;
    }
};
struct Ea {
    void* vt;
    int a4;
    int a8;
    u8 ac, ad;
    s16 ax, ay, az;
    s16 a14;
    u8 p16[2];
    f32 a18, a1c;
    Col c;
    f32 a24;
};
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
struct Bar {
    WF w;
    s16 a40, a42, a44;
    u8 a46;
    int a48;
    int a4c;
    int a50;
    Ea e[2];
};
struct TL {
    WF w;
    u8 p40[0xC];
    WF* a4c;
    Bar* a50;
};
static inline int dep(WF* w) { return w->a26; }
static inline s16 wW(WF* w) { return w->x1 - w->x0; }
static inline s16 wH(WF* w) { return w->y1 - w->y0; }
static inline s16 iW(WF* w) { return w->ix1 - w->ix0; }
static inline s16 iH(WF* w) { return w->iy1 - w->iy0; }
static inline void setInner(WF* w, s16 x0, s16 y0, s16 x1, s16 y1) {
    w->ix0 = x0;
    w->iy0 = y0;
    w->ix1 = x1;
    w->iy1 = y1;
}
static inline void wfRect(WF* w, s16 x, s16 y, s16 cw, s16 ch, s16 a26, int fl) {
    wfInit(w, x, y, x + cw, y + ch, cw, ch, a26, fl);
}
static inline void setPos(Ea* e, s16 x, s16 y, s16 z) { e->ax = x; e->ay = y; e->az = z; }
extern "C" {
void fn_802414C4(TL* t) {
    setInner(&t->w, 6, 3, wW(&t->w) - 6, wH(&t->w) - 3);
    t->w.tx = 0x10;
    t->w.ty = 0x18;
    if (t->a4c) {
        ((WCh*)t)->remove(t->a4c, 0);
    }
    {
        WF* o = (WF*)fn_80079150(0x40);
        if (o) {
            int z = t->w.a26;
            wfInit(o, 0x1a, -0xf, 0x18a, 9, 0x170, 0x18, z - 5, 0x10);
            o->vt = lbl_80390F54;
            ((Lst*)o)->v2C();
        }
        t->a4c = o;
        fn_801E2F40(t, o);
    }
    if (t->a50) {
        ((WCh*)t)->remove(t->a50, 0);
    }
    {
        Bar* o = (Bar*)fn_80079150(0xa4);
        if (o) {
            Col k0, k1;
            int x = iW(&t->w) - 0x10;
            int h = iH(&t->w) - 0x20;
            wfRect(&o->w, x, 0x18, 8, h, t->w.a26 - 5, 0x10);
            o->w.vt = lbl_8038CD64;
            o->a40 = 0;
            o->a42 = 0;
            o->a44 = 0;
            o->a46 = 1;
            o->a48 = 1;
            o->a4c = 0;
            o->a50 = 0;
            { Ea* m = &o->e[0]; eaArrow(m, 2, k0); }
            { Ea* m = &o->e[1]; eaArrow(m, 3, k1); }
            o->w.vt = lbl_8038CA88;
            o->w.iy0 = 0x18;
            o->w.iy1 = wH(&o->w) - 0x18;
            s16 cx = (iW(&o->w) + 1) >> 1;
            s16 hh = (s16)((VO0N*)&o->e[1])->v24() >> 1;
            setPos(&o->e[0], cx, -(hh + o->w.iy0), 0);
            setPos(&o->e[1], cx, hh + iH(&o->w) + (s16)(wH(&o->w) - o->w.iy1), 0);
        }
        t->a50 = o;
        fn_801E2F40(t, o);
    }
}
}
