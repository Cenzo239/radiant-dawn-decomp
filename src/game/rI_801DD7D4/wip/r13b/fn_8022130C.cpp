#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
#pragma inline_max_size(20000)
#pragma inline_depth(16)
extern "C" {
f32 fn_80062850(void*);
void* fn_801E5640(void*, int, int);
void fn_801E5558(void*, void*, int);
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[0x130];
extern char lbl_80371CCC[];
extern u8 lbl_8038FC08[], lbl_8038CD98[], lbl_8038CE68[], lbl_8038CE30[], lbl_8038CA50[], lbl_8038CA18[];
void fn_8021FEC8(void* p);
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
struct K58 { WF w; void* a40; u8 a44; u8 a45[8]; };
struct K50 { WF w; void* a40; u8 a44; };
struct WA { WF w; const char* a40; s16 a44; u8 a46; };
struct S15 { u8 p[0x48]; L84* a48; K58* a4c; K50* a50; WA* a54; W114* a58; };
struct HH { u8 p[0x64]; const char* a64; };
static inline WA* newWA(void) {
    WA* o = (WA*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1c2, 0x10);
        o->w.vt = lbl_8038CA50;
        o->a40 = 0;
        o->a44 = 0x20;
        o->a46 = 0;
        ((VO0N*)o)->v2C();
        o->w.vt = lbl_8038CA18;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline L84* newK84(void) {
    L84* o = (L84*)fn_80079150(0x84);
    if (o != NULL) {
        gInit((G40*)o, 0, 0x1c, 0x260, 0xe4, 0x260, 0xc8, 0x226, 0x10);
        o->w.vt = lbl_8038CD00;
        o->a4c = 0;
        o->a50 = 1;
        o->a51 = 0;
        o->a52 = 0;
        o->a56 = -0x8000;
        o->a58 = -0x8000;
        o->a5a = 0;
        o->a5c = 3;
        o->a5e = 0x1e;
        o->a60 = 0.0f;
        o->a64 = 0;
        o->a70 = 0;
        {LN* l = &o->l74; l->next = l; l->prev = l;}
        o->a7c = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline K58* newK58(void) {
    K58* o = (K58*)fn_80079150(0x58);
    if (o != NULL) {
        wfInit(&o->w, 0x20, 0xc0, 0x120, 0x19c, 0x100, 0xdc, 0x1c2, 0x10);
        o->w.vt = lbl_8038CE68;
        o->a40 = 0;
        o->a44 = 0;
        o->a45[7] = 0; o->a45[6] = 0; o->a45[5] = 0; o->a45[4] = 0; o->a45[3] = 0; o->a45[2] = 0; o->a45[1] = 0; o->a45[0] = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline K50* newK50(void) {
    K50* o = (K50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x129, 0x12d, 0x241, 0x19c, 0x118, 0x6f, 0x1c2, 0x10);
        o->w.vt = lbl_8038CE30;
        o->a40 = 0;
        o->a44 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void addAll(Lst* l, u8* u) { for (; u != NULL; u = *(u8**)(u + 0xe8)) l->v30(u); }
static inline const char* gs() { return lbl_80371CCC + 0x75; }
static inline void s4(S15* s, s16 i, s16 k, const char* q) { s->a54->w.id = i; const char* r = q; s->a54->w.a28 = k; s->a54->w.sy = 0.0f; s->a54->a40 = r; }
static inline void s5(S15* s, const char* q, s16 i, s16 k) { s->a54->w.id = i; s->a54->w.a28 = k; s->a54->w.sy = 0.0f; s->a54->a40 = q; }
static inline void s6(S15* s, const char* const& q) { s->a54->w.id = 0x80; s->a54->w.a28 = 8; s->a54->w.sy = 0.0f; s->a54->a40 = q; }
static inline void iq(const char*& r) { r = lbl_80371CCC + 0x75; }
static inline void iq2(const char** r) { *r = lbl_80371CCC + 0x75; }
void fn_8022130C(S15* s) {
    void* g = *(void**)lbl_803CA870;
    {
        HH* h = (HH*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) fn_801E5558(s, h, 0);
    }
    {
        WA* r = newWA();
        s->a54 = r;
        if (r != NULL) r->w.rc++;
    }
    /*X*/
    {
        L84* r = newK84();
        s->a48 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a48->w.id = 0x81;
    s->a48->w.a28 = 8;
    s->a48->w.sy = 0.0f;
    addAll((Lst*)s->a48, (u8*)lbl_804CB814[0]);
    addAll((Lst*)s->a48, (u8*)lbl_804CB814[0xf]);
    {
        L84* l = s->a48;
        l->a7c = fn_8021FEC8;
        l->a80 = 0;
    }
    s->a48->w.sz = 0.5f;
    {
        K58* r = newK58();
        s->a4c = r;
        if (r != NULL) r->w.rc++;
    }
    s->a4c->w.id = 0x82;
    s->a4c->w.a28 = 8;
    s->a4c->w.sy = 0.0f;
    s->a4c->a40 = fn_801E7A28(s->a48);
    {
        K50* r = newK50();
        s->a50 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a50->w.id = 0x83;
    s->a50->w.a28 = 8;
    s->a50->w.sy = 0.0f;
    s->a50->a44 = 1;
    s->a50->a40 = fn_801E7A28(s->a48);
    {
        W114* r = newW114();
        s->a58 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a58->w.id = 0x84;
    s->a58->w.a28 = 8;
    s->a58->w.sy = 0.0f;
    s->a58->a40 = g;
}
}
