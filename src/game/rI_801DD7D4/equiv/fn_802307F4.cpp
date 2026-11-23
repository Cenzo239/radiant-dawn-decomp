/* fn_802307F4 (0x240): enters the "unit chosen" step of the shop: hides widget 5 if it is visible, slides
 * widget 0xb to x=0x149, formats the unit name line into the message buffer and plays voice cue a24.
 * Sibling of fn_80230A34. Class `regs` (round 20): same instructions, order and references; two saved
 * registers (r29/r30) are swapped in the formatter. Self-contained copy of fn_80225DB4.cpp's
 * declarations (other exported functions reduced to prototypes). */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4D1C(void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
void fn_801EA538(void*, void*);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
void* fn_8010B22C(int);
int fn_8011B8A4(void*);
void* fn_8014C2AC(void*);
extern char lbl_80371E1C[];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_8038FB98[];
void fn_80232864(void* p, void* arg);
struct XY { s16 x, y; };
class MV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*); };
struct Wy { void* vt; int rc; s16 id; s16 x, y; u8 pe[0x22]; f32 a30, a34; u8 p38[4]; Wy* parent; const char* a40; u8 p44[8]; u8 a4c, a4d, a4e, p4f; u8 a50, a51; u8 p52[2]; void* a54; u8 p58[8]; u8 a60; u8 p61[7]; u8 a68; u8 p69[0x13]; void* a7c; int a80; };
static inline void mv(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv3(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
struct HH { u8 p[0x64]; const char* a64; };
static inline void setHelpR(void* s, const char* const& str) { HH* h = (HH*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    Wy* p; Wy* q; Wy* r; Wy* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
#define FIND(v, id_, fld) v = (Wy*)fn_801E5640(s, id_, 0); if (v == NULL) { v = s->fld; fn_801E5448(s, v); }
struct S4 { u8 p[0x44]; Wy* a44; Wy* a48; Wy* a4c; Wy* a50; };
void fn_80225DB4(S4* s);

struct S3 { u8 p[0x7c]; Wy* a7c; u8 p80[8]; struct { u8 p[0x48]; void* a48; u8 p4c[0x44]; const char* a90; }* a88; };
void fn_80233000(S3* s);

struct WU { WF w; f32 a40; void* a44; void* a48; };
static inline WU* newU(void) {
    WU* o = (WU*)fn_80079150(0x4c);
    if (o != NULL) {
        wfInit(&o->w, 0x191, 0x45, 0x297, 0x13b, 0x106, 0xf6, 0x1b8, 0x10);
        o->w.vt = lbl_8038FB98;
        o->a40 = -1.0f;
        o->a44 = 0;
        o->a48 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void newUnit(void* s, void* u) {
    WU* o = newU();
    o->w.id = 0x86;
    o->w.a28 = 8;
    {
        void* g = *(void**)lbl_803CA870;
        f32 f;
        o->a44 = g;
        f = g != NULL ? (f32)fn_8011B8A4((u8*)g + 0x12c) : -1.0f;
        o->a40 = f;
    }
    o->a48 = u;
    fn_801E5448(s, o);
    mv(s, (Wy*)o, 0x13d, o->w.y0, 1);
}
void fn_80227528(void* s);


void fn_801E41E4(void*, void*, void*, int);
static inline void mv2(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E41E4(s, w, &p, f); }
s16 fn_802225E8(void*, int);
void** fn_8022291C(void*);
extern u8 lbl_8038FBD0[];
struct WQ { WF w; void* a40; };
struct S5 { u8 p[0x48]; Wy* a48; u8 p4c[0xc]; Wy* a58; };
static inline WQ* newQ(void) {
    WQ* o = (WQ*)fn_80079150(0x4c);
    if (o != NULL) {
        wfInit(&o->w, 0x191, 0x45, 0x297, 0x10b, 0x106, 0xc6, 0x1cc, 0x10);
        o->w.vt = lbl_8038FBD0;
        o->a40 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
struct LS { u8 p[0x4c]; u8 a4c; u8 p4d[3]; s16 a50; };
static inline s16 clampPos(s16 v) { return v < 0 ? 0 : v; }
void fn_801E4F50(void*, void*, int);
struct S6 { u8 p[0x88]; struct { u8 p[0x4c]; void* a4c; u8 p50[0x28]; void* a78; }* a88; };
struct W7 { u8 p[0x4e]; u8 a4e; u8 p4f[0x19]; u8 a68; };
void fn_802336E8(S6* s);

void fn_80233944(S6* s);


void fn_801E5954(void*);
void fn_80253EE4(const char*, f32);
extern char lbl_80372600[];
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CAB38[];
int fn_80060754(void*);
int* fn_801059B0(void);
int fn_80105158(int*);
void fn_801E6C44(void*, void*, int);
void fn_801E6D50(void*, void*);
class TW { public: virtual int v08(int); virtual int v0C(int); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*); };
struct RC { void* vt; int rc; };
struct S8 { u8 p[0x81]; u8 a81; u8 p82[6]; struct { u8 p[0x68]; void* a68; u8 p6c[0x10]; void* a7c; u8 p80[0x24]; const char* aa4; }* a88; };
static inline void rel(RC* p) {
    if (p != NULL) {
        if (--p->rc == 0 && p != NULL) ((TW*)p)->v08(1);
    }
}
void fn_80233324(S8* s);


void* fn_802167C8(void*, int, int, int, int, int, int);
void fn_8021A434(void*, void*);
void fn_8021CCF0(void*, int);
void* fn_8021CD4C(void*);
struct C4 { s8 r, g, b, a; };
C4* fn_8021CD58(void*);
void fn_800D0B38(int, void*);
void* fn_8024BC94(void);
const char* fn_8010F5E0(void*);
int fn_8010F64C(void*, int);
void fn_80290DDC(char*, const char*, ...);
int fn_8010B228(void*);
extern u8 lbl_8038F8D0[], lbl_8038F898[], lbl_8038F7F0[];
extern u8 lbl_80390B4C[];
struct WP { void* vt; u8 p[0x70]; u8 a74; u8 p75[0x13]; int a88; };
struct WN { WF w; s8 a40; int a44; u8 a48; };
struct Un { u8 p[0x16]; u16 a16; };
struct S9 { u8 p[0x70]; struct { u8 p[0x70]; void* a70; }* a70; Wy* a74; u8 p78[0x10]; struct { u8 p[0x24]; void* a24; void* a28; u8 p2c[0xc]; void* a38; void* a3c; u8 p40[0x64]; const char* aa4; }* a88; };
static inline WP* newP(void) {
    WP* o = (WP*)fn_80079150(0x8c);
    if (o != NULL) {
        fn_802167C8(o, 0x198, 0x66, 0x104, 0xda, 0x1e0, 1);
        o->vt = lbl_8038F8D0;
        o->a74 = 0;
        o->a88 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline WN* newN(void) {
    WN* o = (WN*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x19d, 0x13c, 0x293, 0x19c, 0xf6, 0x60, 0x1c2, 0x10);
        o->w.vt = lbl_8038F898;
        o->a40 = -1;
        o->a44 = fn_8010B228(lbl_80390B4C);
        o->a48 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void fmtUnit(char* buf, WN* w) {
    switch (*((s8*)fn_8024BC94() + 0x1bc8)) {
    case 0: {
        Un* u = (Un*)w->a44;
        int id = u->a16;
        fn_80290DDC(buf, lbl_80372600 + 0x6b, id + 0x80, 0x22, fn_8010F5E0(u));
        break;
    }
    case 1: {
        int k;
        const char* n;
        Un* u = (Un*)w->a44;
        n = fn_8010F5E0(u);
        k = fn_8010F64C(u, 0);
        fn_80290DDC(buf, lbl_80372600 + 0x7c, k, 0x22, n, u->a16 + 0x80);
        break;
    }
    default: {
        Un* u = (Un*)w->a44;
        int id = u->a16;
        fn_80290DDC(buf, lbl_80372600 + 0x6b, id + 0x80, 0x22, fn_8010F5E0(u));
        break;
    }
    }
}
void fn_80230A34(S9* s);

struct S10 { u8 p[0x70]; struct { u8 p[0x70]; void* a70; }* a70; u8 p74[0x14]; struct { u8 p[0x38]; void* a38; void* a3c; u8 p40[0x64]; const char* aa4; }* a88; };
struct WO { WF w; s8 a40; u8 p41[3]; void* a44; };
static inline WO* newO(void) {
    WO* o = (WO*)fn_80079150(0x48);
    if (o != NULL) {
        wfInit(&o->w, -0x2c, 0x50, 0xcc, 0x190, 0xf8, 0x140, 0x226, 0x10);
        o->w.vt = lbl_8038F7F0;
        o->a40 = -1;
        o->a44 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
void fn_80231DC0(S10* s);

void fn_800D3C30(void*, int);
void* fn_80081194(void*, void*);
extern u8 lbl_8038F828[], lbl_80390A38[];
struct WR { WF w; int a40; LN l44; int a4c, a50, a54, a58, a5c; u8 a60; s8 a61; u8 p62[6]; u8 a68; u8 p69; s16 a6a, a6c, a6e; };
struct PR { u8 p[0x30]; u8 a30; s8 a31; s8 a32; u8 p33[5]; void* a38; };
struct S11 { u8 p[0x88]; struct { u8 p[0x30]; void* a30; u8 p34[0x60]; const char* a94; }* a88; void* a8c; };
static inline WR* newR(void) {
    WR* o = (WR*)fn_80079150(0x70);
    if (o != NULL) {
        gInit((G40*)o, 4, 0x74, 0x25c, 0x12a, 0x258, 0xb6, 0x244, 0x10);
        o->w.vt = lbl_8038F828;
        o->a60 = 0;
        o->a61 = -1;
        o->a68 = 0;
        o->a6a = 0;
        o->a6c = -0x8000;
        o->a6e = -0x8000;
        o->a4c = 0; o->a50 = 0; o->a54 = 0; o->a58 = 0; o->a5c = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
void fn_800451D4(void*, void*);
void fn_801E6B64(const char*, void*, f32, f32);
int fn_801204E8(void*);
f32 fn_8021DA10(void*, int);
f32 fn_80062850(void*);
void* fn_8011A158(void*);
extern char lbl_80371CCC[];
extern u8 lbl_8038FB60[];
class SV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*); virtual int v38(); virtual u32 v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*); };
struct SS { u8 p[0x40]; u8 a40; };
static inline void popup(const char* m, void* s, XY p) { f32 x = p.x; f32 y = p.y; fn_801E6B64(m, s, x, y); }
static inline XY mk(u32 r) { XY q; q.x = r >> 16; q.y = r; return q; }
static inline void msgAt(const char* m, void* s, Wy* a) {
    popup(m, s, mk(((SV*)a)->v3C()));
}
static inline void mv6i(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void mv6j(void* s, Wy* w, s16 x, s16 y, int f) { mv6i(s, w, x, y, f); }
static inline void mv6(void* s, Wy* w, s16 x, s16 y, int f) { mv6j(s, w, x, y, f); }
static inline void fz(void* s, Wy* a) {
    f32 v0, v1, v2, v3;
    Wy* r; Wy* q; Wy* p; Wy* t2;
    v0 = a->a34; p = a->parent;
    if (p) { v1 = p->a34; q = p->parent; if (q) { v2 = q->a34; r = q->parent; if (r) { v3 = r->a34; t2 = r->parent; if (t2) { v3 *= fn_801E3468(t2); } v2 *= v3; } v1 *= v2; } v0 *= v1; }
    if (0.5f != v0) fn_801E518C(s, a, 0, 0.5f);
}
void fn_8022609C(SS* s);

void fn_80220198(SS* s);

struct WQ2 { WF w; void* a40; };
static inline WQ* newQ2(void) { return newQ(); }
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
struct S12 { u8 p[0x58]; WQ2* a58; };
void fn_80227B2C(S12* s);

template <class T> static inline void mvRi(void* s, T*& w, s16 x) { XY p; s16 y = ((Wy*)w)->y; p.x = x; p.y = y; fn_801E495C(s, w, &p, 0); }
template <class T> static inline void mvRj(void* s, T*& w, s16 x) { mvRi(s, w, x); }
template <class T> static inline void mvR(void* s, T*& w, s16 x) { mvRj(s, w, x); }
int fn_802172F8(void*);
int fn_801A2224(void*);
void fn_801A1DCC(void*, int, f32, f32);
void fn_801A1AC4(void*, void*, int, f32, f32);
void fn_801A1CFC(void*);
void fn_801A1F64(void*, void*, f32, f32);
void fn_801A1BE0(void*, void*, void*, f32, f32);
struct Ms { u32 fl; u8 p[0x100]; };
extern Ms lbl_8041EB20;
class LV { public: virtual int v08(int); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual u32 v30(); virtual int v34(void*); virtual int v38(int); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual u32 v4C(); virtual int v50(void*); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(int); };
struct S13 { u8 p[0x40]; u32 a40; u8 p44[0x28]; LV* a6c; u8 p70[0x11]; u8 a81; f32 a84; struct { u8 p[0xc]; void* ac; u8 p10[0x40]; void* a50; u8 p54[0xc]; void* a60; u8 p64[0x38]; const char* a9c; u8 pa0[4]; const char* aa4; }* a88; };
struct WB4 { u8 p[0x44]; int a44; };
static inline void sf2(int off) { fn_80253EE4(lbl_80372600 + off, 0.0f); }
static inline void shA(LV* a) {
    XY c = mk(a->v4C());
    int v = a->v48();
    f32 x = c.x; f32 y = c.y;
    fn_801A1DCC(&lbl_8041EB20, v, x, y);
}
static inline void shB(void* s, LV* a) {
    XY c = mk(a->v4C());
    int v = a->v48();
    f32 x = c.x; f32 y = c.y;
    fn_801A1AC4(&lbl_8041EB20, s, v, x, y);
    lbl_8041EB20.fl |= 2;
}
void fn_8022EBB8(S13* s);

u32 fn_80217ABC(void*);
void fn_80110BB4(void*, u32);
int fn_80111074(void*);
int fn_800626E0(void*);
void fn_8022E7A0(void*);
struct C0 { void* vt; int rc; };
static inline void setUnit(S13* s, u32 v) {
    if (s->a40 != v) fn_80110BB4(&s->a40, v);
}
void fn_8022F1A8(S13* s);

void* fn_8011A0A8(void*);
int fn_80105194(void*);
int fn_80129A8C(void*);
struct It2 { u8 p[0x1c]; u8 a1c; u8 p1d[3]; u8 a20; };
class LI { public: virtual int v08(int); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual u32 v30(); };
static inline void* curOf(void* a) { void* r; if (fn_8022291C(a) != NULL) { r = *fn_8022291C(a); } else { r = NULL; } return r; }
struct S14 { u8 p[0x58]; C0* a58; };
static inline BOOL canUse(void) {
    if (fn_80060754(lbl_803CAB38) != 0 && fn_80105194(fn_801059B0()) >= 0) return 1;
    return ((u32)fn_80129A8C(*(void**)lbl_803CA870) >> 31) ^ 1;
}
static inline void msgAt2(const char* m, void* s, void* a) {
    popup(m, s, mk(((LI*)a)->v30()));
}
static inline void sh1(void* a, void* cur) {
    XY c = mk(((LI*)a)->v30());
    void* v = fn_8011A0A8(cur);
    f32 x = c.x; f32 y = c.y;
    fn_801A1DCC(&lbl_8041EB20, (int)v, x, y);
}
static inline void sh2(void* s, void* a, void* cur) {
    XY c = mk(((LI*)a)->v30());
    void* v = fn_8011A0A8(cur);
    f32 x = c.x; f32 y = c.y;
    fn_801A1AC4(&lbl_8041EB20, s, (int)v, x, y);
    lbl_8041EB20.fl |= 2;
}
void fn_80228118(S14* s);

extern u8 lbl_8038CE68[], lbl_8038CE30[];
void fn_8021FEC8(void* p);
struct K58 { WF w; void* a40; u8 a44; u8 a45[8]; };
struct K50 { WF w; void* a40; u8 a44; };
struct S15 { u8 p[0x48]; L84* a48; K58* a4c; K50* a50; };
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
void fn_8021FA30(S15* s);

int fn_80112364(void*, int, int, int, int);
class LS2 { public: virtual int v08(int); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(int); virtual int v34(); virtual int v38(int); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual u32 v4C(); };
struct Bf { u8 p5[5]; u8 b0 : 2; u8 fl : 1; u8 b3 : 5; };
struct S16 { u8 p[0x40]; u32 a40; u8 p44[0x28]; Wy* a6c; struct LS3 { LS2* d; }* dummy; u8 p74[0x10]; f32 a84; struct { u8 p[0x10]; void* a10; u8 p14[0x4c]; void* a60; u8 p64[0x28]; const char* a8c; u8 p90[0x14]; const char* aa4; }* a88; };
struct LI3 { void* vt; u8 p[0x6c]; Bf* a70; };
#define L70(s) (*(LI3**)((u8*)(s) + 0x70))
u32 fn_8022A87C(void*);
void fn_8022BC00(void*, u32);
void fn_8022BA6C(void*, int);
void fn_8022B9B8(void*, int);
extern char lbl_80372034[];
class FO { public: virtual int v08(); virtual int v0C(); virtual void* v10(int, int); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(void*); virtual int v2C(); virtual int v30(int); };
void fn_8022D9E0(void* s);

void fn_8022BB24(void*);
void fn_8022B758(void*, const char*);
void fn_8022B880(void*, int);
void fn_800453B4(void*, int);
struct S20 { u8 p[0x40]; int a40; int a44; char a48[1]; const char* a4c; };
struct S21 { u8 p[0x40]; int a40; u32 a44; const char* a48; const char* a4c; };
class FP { public: virtual int v08(); virtual int v0C(); virtual void* v10(int, int); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(void*); virtual int v2C(); virtual int v30(int); virtual int v34(); virtual int v38(int); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual u32 v4C(); };
static inline const char* nm(S21* s) { return (s->a44 >> 31) == 0 ? (char*)s + 0x45 : s->a4c; }
void fn_8022D508(S21* s);

struct S22 { u8 p[0x44]; int a44; u8 p48[0x10]; struct { void* vt; int rc; u8 p8[0x40]; int a48; }* a58; };
void fn_80220B78(S22* s);

void fn_802313D0(S11* s);

void* fn_80081050(void*, void*);
struct PR2 { u8 p[0x30]; u8 a30; s8 a31; s8 a32; u8 p33; void* a34; void* a38; };
void fn_800D3BCC(void*, int);

struct WR2 { void* vt; u8 p4[0x48]; int a4c[5]; u8 a60; u8 p61[7]; u8 a68; u8 p69; s16 a6a; };
struct S23 { u8 p[0x8c]; void* a8c; };
static inline int rSel(WR2* a) { return a->a4c[a->a6a]; }
class FO2 { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual u32 v34(); };
void fn_802315E8(S23* s);

void* fn_80223998(void*);
class LV2 { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual u32 v3C(); };
int fn_80127A90(void*);
int fn_8011B680(void*, void*);
int fn_80119F24(void*, void*);
struct It3 { u8 p[0x1c]; u8 a1c; u8 p1d; u8 a1e; };
struct S24 { u8 p[0x54]; Wy* a54; Wy* a58; };
template <class T> static inline void mvR1(void* s, T*& w, s16 x) { XY p; s16 y = ((Wy*)w)->y; p.x = x; p.y = y; fn_801E495C(s, w, &p, 1); }
template <class T> static inline void mvRa(void* s, T*& w, s16 x) { mvR1(s, w, x); }
static inline void msg3(const char* m, void* s, void* a) { popup(m, s, mk(((LV2*)a)->v3C())); }
static inline void sha(void* a, void* cur) {
    XY c = mk(((LV2*)a)->v3C());
    void* v = fn_8011A0A8(cur);
    f32 x = c.x; f32 y = c.y;
    fn_801A1DCC(&lbl_8041EB20, (int)v, x, y);
}
static inline void shb(void* s, void* a, void* cur) {
    XY c = mk(((LV2*)a)->v3C());
    void* v = fn_8011A0A8(cur);
    f32 x = c.x; f32 y = c.y;
    fn_801A1AC4(&lbl_8041EB20, s, (int)v, x, y);
    lbl_8041EB20.fl |= 2;
}
static inline void rel2(Wy*& w) {
    C0* p = (C0*)w;
    if (p) {
        if (--p->rc == 0 && p) ((LI*)p)->v08(1);
        w = 0;
    }
}
void fn_80226DF8(S24* s);

extern u8 lbl_8038FA38[], lbl_8038E160[];
void fn_8014BED4(void*, void*);
void* fn_800D4188(const char*, void*);
struct W74 { void* vt; u8 p[0x6c]; int a70; };
struct WH { WF w; int a40; int a44; };
struct S27 { u8 p[0x68]; W74* a68; u8 p6c[0xc]; WH* a78; u8 p7c[0xc]; struct { void* a0; u8 p4[0x9c]; const char* aa0; }* a88; void* a8c; };
static inline W74* newW74(void) {
    W74* o = (W74*)fn_80079150(0x74);
    if (o != NULL) {
        fn_802167C8(o, 0xe0, 0x66, 0x158, 0xda, 0x226, 0);
        o->vt = lbl_8038FA38;
        o->a70 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline WH* newWH(void) {
    WH* o = (WH*)fn_80079150(0x48);
    if (o != NULL) {
        wfInit(&o->w, 0x14e, 0x149, 0x236, 0x173, 0xe8, 0x2a, 0x226, 0x10);
        o->w.vt = lbl_8038E160;
        o->a40 = 0;
        o->a44 = -1;
        ((VO0N*)o)->v2C();
    }
    return o;
}
void fn_8022E2D0(S27* s);

u32 fn_80110F08(void*);
void fn_8022DE0C(void*, const char*, int, void*);
struct S28 { u8 p[0x70]; struct { u8 p[0x70]; void** a70; }* a70; u8 p74[0x14]; struct { u8 p[0x40]; void* a40; void* a44; u8 p48[0x68]; const char* ab0; }* a88; };
static inline void pick(S28* s) {
    u16 id;
    void** u;
    const char* n;
    Un* r;
    u = s->a70->a70;
    r = (Un*)u[0];
    if (r != NULL) id = r->a16; else id = 0;
    n = fn_8010F5E0(r);
    fn_8022DE0C((void*)fn_80110F08(u), n, (u8)id + 0x81, s);
}
void fn_802326F0(S28* s);

void fn_802327A4(S28* s);

}

/* ---- from build/tmp/r20i/frag_07F4.cpp ---- */
extern "C" {
void fn_802307F4(S9* s) {
    Wy* a;
    f32 v3, v2, v1, v0;
    char buf[0x40];
    FIND(a, 5, a74)
    CHAIN(a, a30, fn_801E33B4, v0, v1, v2, v3)
    if (1.0f != v0) fn_801E4D1C(s, a, 0);
    a = (Wy*)fn_801E5640(s, 0xb, 0);
    if (a->x != 0x149) mv(s, a, 0x149, a->y, 0);
    fmtUnit(buf, (WN*)a);
    fn_800D0B38(0, buf);
    fn_8014C2AC(s->a88->a24);
}
}
