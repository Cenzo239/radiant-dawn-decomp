#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
#pragma inline_max_size(20000)
#pragma inline_depth(16)
extern "C" {
f32 fn_80062850(void*);
extern u8 lbl_803CAB38[];
extern u8 lbl_8038FC08[], lbl_8038CD98[];
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
static inline void eaPlain(Ea* m, int d) {
    eaBase(m, d);
    m->vt = lbl_8038C260;
    ((VO0N*)m)->v0C();
}
struct W114 { WF w; void* a40; f32 a44; int a48; Ea e[5]; };
struct S17 { u8 p[0x48]; void* a48; u8 p4c[0xc]; W114* a58; };
static inline W114* newW114(void) {
    W114* o = (W114*)fn_80079150(0x114);
    if (o != NULL) {
        Col k0, k1, k2, k3;
        wfInit(&o->w, 0, 0x3b, 0x260, 0xb1, 0x260, 0x76, 0x1f4, 0x10);
        o->w.vt = lbl_8038FC08;
        o->a40 = 0;
        o->a44 = fn_80062850(lbl_803CAB38);
        o->a48 = 0;
        { Ea* m = &o->e[0]; eaArrow(m, 2, k0); }
        { Ea* m = &o->e[1]; eaArrow(m, 3, k1); }
        { Ea* m = &o->e[2]; eaArrow(m, 0, k2); }
        { Ea* m = &o->e[3]; eaArrow(m, 1, k3); }
        { Ea* m = &o->e[4]; eaPlain(m, 2); }
        ((VO0N*)o)->v2C();
    }
    return o;
}
void fn_8022052C(S17* s) {
    void* x = fn_801E7A28(s->a48);
    {
        W114* r = newW114();
        s->a58 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a58->w.id = 0x84;
    s->a58->w.a28 = 8;
    s->a58->w.sy = 0.0f;
    s->a58->a40 = x;
    fn_801E5448(s, s->a58);
}
void* fn_801E5640(void*, int, int);
void fn_80218A48(void*, void*);
extern u8 lbl_8038F934[];
struct WF2 { void* vt; u8 p4[0x6c]; u8 a70[4]; s16 a74; u8 p76[2]; Ea e[8]; int a1b8, a1bc; };
struct S18 { u8 p[0x40]; u8 a40[0x30]; WF2* a70; u8 p74[0x14]; struct { u8 p[0x8c]; const char* a8c; }* a88; };
void* fn_802167C8(void*, int, int, int, int, int, int);
static inline WF2* newF2(void) {
    WF2* o = (WF2*)fn_80079150(0x1c0);
    if (o != NULL) {
        Col k4, k5, k6, k7;
        fn_802167C8(o, 0x134, 0x66, 0x160, 0xda, 0x46, 1);
        o->vt = lbl_8038F934;
        *(int*)o->a70 = 0;
        o->a74 = 0;
        { Ea* m = &o->e[0]; eaPlain(m, 1); }
        { Ea* m = &o->e[1]; eaPlain(m, 1); }
        { Ea* m = &o->e[2]; eaPlain(m, 1); }
        { Ea* m = &o->e[3]; eaPlain(m, 1); }
        { Ea* m = &o->e[4]; eaArrow(m, 0, k4); }
        { Ea* m = &o->e[5]; eaArrow(m, 1, k5); }
        { Ea* m = &o->e[6]; eaArrow(m, 2, k6); }
        { Ea* m = &o->e[7]; eaArrow(m, 3, k7); }
        o->a1b8 = 0;
        o->a1bc = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
struct HH { u8 p[0x64]; const char* a64; };
static inline void setHelpR(void* s, const char* const& str) { HH* h = (HH*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
class FV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(int); };
void fn_8022F67C(S18* s) {
    {
        WF2* r = newF2();
        s->a70 = r;
        if (r != NULL) ((WF*)r)->rc++;
    }
    ((WF*)s->a70)->id = 2;
    ((FV*)s->a70)->v38(0);
    ((WF*)s->a70)->a28 = 8;
    fn_80218A48(s->a70, s->a40);
    fn_801E5448(s, s->a70);
    { void* t = s; const char* h = s->a88->a8c; setHelpR(t, h); }
}
extern u8 lbl_8038CD64[], lbl_8038CA88[], lbl_80390468[];
void fn_8022A5F8(void*, int, int, int, s16);
class HO { public: virtual int v08(); virtual int v0C(void*, int); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); };
struct SB { WF w; s16 a40, a42, a44; u8 a46; u8 p47; int a48, a4c, a50; Ea e0, e1; };
struct HS { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; };
static inline s16 ihW(HS* o) { return o->ix1 - o->ix0; }
static inline s16 ihH(HS* o) { return o->iy1 - o->iy0; }
static inline s16 hW(HS* o) { return o->x1 - o->x0; }
static inline s16 hH(HS* o) { return o->y1 - o->y0; }
static inline void setI(HS* o, int a, int b, int c, int d) { o->ix0 = a; o->iy0 = b; o->ix1 = c; o->iy1 = d; }
static inline void rmc(HO* o, void* c) { if (c != NULL) o->v0C(c, 0); }
static inline void wfInit2(WF* w, int x, int y, int ww, int hh, s16 a) { s16 x1 = (s16)x + ww; s16 y1 = (s16)y + hh; wfInit(w, x, y, x1, y1, ww, hh, a, 0x10); }
static inline void apos(SB* o, s16 cx, s16 r) {
    s16 m = r >> 1;
    o->e0.ax = cx;
    o->e0.ay = -(m + o->w.iy0);
    o->e0.az = 0;
    o->e1.ax = cx;
    o->e1.ay = (s16)((s16)(o->w.y1 - o->w.y0) - o->w.iy1) + (s16)(o->w.iy1 - o->w.iy0) + m;
    o->e1.az = 0;
}
static inline SB* newSB(HS* p) {
    SB* o = (SB*)fn_80079150(0xa4);
    if (o != NULL) {
        Col k1, k0;
        s16 a = p->a26;
        s16 xo = ihW(p) - 0x10;
        s16 h = p->iy1 - p->iy0;
        wfInit2(&o->w, xo, 0, 8, h, a - 5);
        o->w.vt = lbl_8038CD64;
        o->a40 = 0; o->a42 = 0; o->a44 = 0;
        o->a46 = 1;
        o->a48 = 1;
        o->a4c = 0; o->a50 = 0;
        { Ea* m = &o->e0; eaArrow(m, 2, k0); }
        { Ea* m = &o->e1; eaArrow(m, 3, k1); }
        o->w.vt = lbl_8038CA88;
        o->w.iy0 = 0x18;
        o->w.iy1 = (s16)(o->w.y1 - o->w.y0) - 0x18;
        {
            s16 cx = ((s16)(o->w.ix1 - o->w.ix0) + 1) >> 1;
            apos(o, cx, ((VO0N*)&o->e1)->v24());
        }
    }
    return o;
}
struct HA { HS h; u8 p[0x74 - sizeof(HS)]; SB* a74; void* a78; HS* a7c; };
struct HB { HS h; u8 p[0x4c - sizeof(HS)]; SB* a4c; };
void fn_80224CCC(HB* o) {
    setI(&o->h, 3, 6, hW(&o->h) - 3, hH(&o->h) - 6);
    o->h.tx = 0x18;
    o->h.ty = 6;
    rmc((HO*)o, o->a4c);
    {
        SB* b = newSB(&o->h);
        o->a4c = b;
        b->a50 = 1;
        fn_801E2F40(o, o->a4c);
    }
}
}
