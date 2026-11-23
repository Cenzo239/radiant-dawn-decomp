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
}
