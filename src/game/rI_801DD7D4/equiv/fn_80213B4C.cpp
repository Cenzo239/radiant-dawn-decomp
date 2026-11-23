/* fn_80213B4C: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* Near misses, snapshot of the batch before pruning:
   fn_80213B4C: 25 of 182 words differ
   fn_80215688: 5 of 104 words differ
   fn_8021C1EC: 11 of 35 words differ
   fn_8021C278: 5 of 41 words differ
   Each function also exists in the live file unless listed here. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void* fn_80079150(u32);

class V3x { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(int); };
void fn_802135E0(V3x* o, int a);


void fn_801E17FC(void*, void*);
int fn_8012EA2C(void*, int);
u8 fn_8012E830(void*);
void* fn_8012E854(void*, int);
void* fn_8012E3A4(void*);
void fn_8007E154(void);
void fn_8007E720(f32);
void fn_8007E174(int, u32);
void fn_8007E164(void);
int fn_800CB0FC(f32, int);
void fn_800800D4(int);
void fn_80176F7C(int, int, int, int, int);
void fn_80080308(void);
void fn_801D9064(int, int, int);
void fn_801E40B0(void*, int);
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_801E5734(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void* fn_801E7A28(void*);
int fn_80058718(void);
int fn_8002460C(void);

extern void* lbl_8038C294[];
extern char lbl_803712F8[];

struct W {
    void* vt;
    int rc;
    s16 id;
    s16 x0, y0, x1, y1;
    s16 ix0, iy0, ix1, iy1;
    u8 pad1a[4];
    s16 tx, ty;
    u8 c[4];
    u8 pad26[0x12];
    u32 flags;
};

#pragma use_lmw_stmw off
class V18 { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); };
void fn_8021363C(V18* o, void* a);

void fn_8021376C(VO0* o);


struct P44 { u8 pad[0x44]; void* vt; };
static inline void m44dtor(P44* p) {
    VO0N* m = (VO0N*)((u32)p + 0x44);
    if (m != NULL) {
        if (m != NULL) {
            p->vt = lbl_8038C294;
            m->v10();
        }
    }
}
void* fn_8021395C(void* p, int del);

void* fn_802139D8(void* p, int del);


#define FREE_FN(name) \
void* name(void* p, int del) { \
    if (p != NULL && del > 0) { \
        fn_80079210(p); \
    } \
    return p; \
}



static inline s16 wW(W* w) { return w->x1 - w->x0; }
static inline s16 wH(W* w) { return w->y1 - w->y0; }
static inline s16 wH2(W* w) { s16 a = w->y0; s16 b = w->y1; return b - a; }
static inline void setI(W* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
static inline void setI2(W* w, int a, int b, int c, int d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
void fn_80213AE0(W* w);

void fn_80213B10(W* w);


class RObj2 { public: virtual void destroy(int); int rc; };
#define REL(f) if (o->f != NULL) { RObj2* r = o->f; if (--r->rc == 0) { if (r != NULL) { r->destroy(1); } } o->f = NULL; }
struct S54 { u8 pad[0x44]; RObj2* a, *b, *c, *d, *e; };
void fn_80213E24(S54* o);


struct Wi { u8 p[0xa]; s16 x, y; u8 p2[0x32]; void* a40; u8 p3[0xc]; u8 b50; u8 p4[3]; void* a54; u8 p5[0xc]; void* a64; };
struct Sc { u8 p[0x40]; int a40; Wi* a44, *a48, *a4c, *a50, *a54; };
struct Pt { s16 x, y; };

static inline void mv(Sc* s, Wi* w, s16 x, s16 y, int f) { Pt p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void setHelp(Sc* s, char* const& str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }


#define FIND(res, id, fld) res = (Wi*)fn_801E5640(s, id, 0); if (res == NULL) { res = s->fld; fn_801E5448(s, res); }

static inline Wi* findOr(Sc* s, int id, Wi*& w0) { Wi* r = (Wi*)fn_801E5640(s, id, 0); if (r == NULL) { r = w0; fn_801E5448(s, r); } return r; }
void fn_80214704(Sc* s);

int fn_80214618(void* u);

void fn_80215024(Sc* s);


extern void* lbl_8038CB1C[]; extern void* lbl_8038CA50[]; extern void* lbl_8038CA18[]; extern void* lbl_8038C1C0[];
struct WF {
    void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; f32 sx, sy, sz; u32 flags; void* a3c;
};
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->id = -1;
    w->x0 = x0; w->y0 = y0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}
struct WA { WF w; void* a40; s16 a44; u8 a46; };
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; void* a64; };
static inline void wbInit(WB* b, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
        wfInit(&b->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
        b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
        b->a50 = 1;
        b->a5a = 0; b->a5e = 0;
        b->w.vt = lbl_8038C1C0;
        b->a60 = 0; b->a64 = 0;
        b->a58 = iy1; b->a5c = iy1;
        b->a54 = 0.75f;
}
void fn_80213B4C(Sc* s) {
    WA* a = (WA*)fn_80079150(0x50);
    WB* b;
    if (a != NULL) {
        wfInit(&a->w, 0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1c2, 0x10);
        a->w.vt = lbl_8038CA50;
        a->a40 = 0;
        a->a44 = 0x20;
        a->a46 = 0;
        ((VO0N*)a)->v2C();
        a->w.vt = lbl_8038CA18;
        ((VO0N*)a)->v2C();
    }
    a->w.id = 0x80;
    a->a40 = lbl_803712F8;
    fn_801E5448(s, a);
    b = (WB*)fn_80079150(0x68);
    if (b != NULL) {
        wbInit(b, 0, 400, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
    }
    b->w.id = -0x1000;
    b->a4c = 1;
    b->a64 = lbl_803712F8 + 0x19;
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(s, b);
    if (fn_80058718() != 0 && fn_8002460C() != 0) {
        WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = 1;
    }
    setHelp(s, lbl_803712F8 + 0x1a);
}

extern VO0N* lbl_804CB5B8;
void fn_801E495C(void*, void*, void*, int);
void fn_801E5954(void*);
void fn_801E6B64(const char*, void*, f32, f32);
void fn_801E6C44(void*, void*, int);
void fn_801E6D50(void*, void*);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_80253EE4(const char*, f32);
int fn_801A2224(void*);
extern char lbl_8041EB20[];
class WV { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual u32 v3C();
 virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*);
};
static inline void mv2(Sc* s, Wi* w, s16 x, s16 y, int f) { Pt p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }

static inline Pt wpos(WV* a) { u32 r = a->v3C(); Pt p0; p0.x = r >> 16; p0.y = r; return p0; }
static inline void msgAt(const char* m, void* s, s16 x, s16 y) { f32 fx = x; f32 fy = y; fn_801E6B64(m, s, fx, fy); }
static inline void msgAt2(const char* const& m, void* s, f32 x, f32 y) { fn_801E6B64(m, s, x, y); }
void fn_8021491C(Sc* s);


struct SP { u8 p[0x3c]; struct SP* parent; u8 p40[0]; };
struct N34 { u8 p[0x34]; f32 z; u32 p38; struct N34* parent; };
f32 fn_801E3468(N34*);
static inline f32 z3(N34* o) { f32 v = o->z; if (o->parent != NULL) { v *= fn_801E3468(o->parent); } return v; }
static inline f32 z2(N34* o) { f32 v = o->z; if (o->parent != NULL) { v *= z3(o->parent); } return v; }
static inline f32 z1(N34* o) { f32 v = o->z; if (o->parent != NULL) { v *= z2(o->parent); } return v; }
static inline f32 z0(N34* o) { f32 v = o->z; if (o->parent != NULL) { v *= z1(o->parent); } return v; }

void fn_801E518C(void*, void*, int, f32);
static inline void animTo(void* s, N34* w, f32 v) { if (v != z0(w)) fn_801E518C(s, w, 0, v); }
#define animB(s, a, k) { \
    f32 v3; f32 v2; f32 v1; f32 v0; N34* p; N34* q; N34* r; N34* o; \
    v0 = a->z; p = a->parent; \
    if (p) { v1 = p->z; q = p->parent; if (q) { v2 = q->z; r = q->parent; if (r) { v3 = r->z; o = r->parent; if (o) { v3 *= fn_801E3468(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    if (k != v0) fn_801E518C(s, a, 0, k); \
}
#define animA(s, a, k) { \
    f32 v0; f32 v1; f32 v2; f32 v3; N34* p; N34* q; N34* r; N34* o; \
    v0 = a->z; p = a->parent; \
    if (p) { v1 = p->z; q = p->parent; if (q) { v2 = q->z; r = q->parent; if (r) { v3 = r->z; o = r->parent; if (o) { v3 *= fn_801E3468(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    if (k != v0) fn_801E518C(s, a, 0, k); \
}
extern u8 lbl_803CA870[0x130];
void fn_80215B44(Sc* s);


void* fn_801E00D0(const char*);
void* fn_801E041C(const char*, const char*);
void* fn_800D5448(void*, void*, int);
void fn_800D56E8(void*);
s8 fn_8012E9B4(void*, void*);
s8 fn_8012E944(void*, void*);
u8 fn_8012E8BC(void*, int);
void fn_8012ED88(void*, int);
void fn_8012EC10(void*, int);
void* fn_8012E390(void*);
void fn_8012E388(void*, int);
void fn_8012E398(void*, void*);
void* fn_80085EF8(u8);
void* fn_800D0864(const char*);
void fn_801ABBA8(void*, const char*, void*, int);
extern u32 lbl_804CB728;

static inline void mv48(Sc* s) { s16 y2 = s->a48->y; Pt p2; p2.x = 0x18c; p2.y = y2; fn_801E495C(s, s->a48, &p2, 0); }
void fn_80215148(Sc* s);


static inline u8* dlg2(const char* no, const char* yes) { return (u8*)fn_801E041C(yes, no); }
#pragma use_lmw_stmw on

void fn_80215688(Sc* s);


#pragma use_lmw_stmw off

void fn_80215828(Sc* s);

void fn_80215984(Sc* s);


static inline void bl1(void* u, void* v) {
}
#define UNLINK(x, y) if (fn_8012E390(x) != NULL) { void* e = *(void**)((u8*)y + 0xec); if (fn_8012E390(x) != e) { \
    int k = fn_8012E944(x, fn_8012E390(x)); \
    fn_8012ED88(x, k); \
    { void* o = fn_8012E3A4(x); if (o != NULL) { k = fn_8012E944(o, *(void**)((u8*)x + 0xec)); fn_8012ED88(o, k); } } } \
}
#define UNLINK2(x, y) if (fn_8012E390(x) != NULL) { void* e = *(void**)((u8*)y + 0xec); if (fn_8012E390(x) != e) { \
    fn_8012E388(fn_8012E3A4(x), 0); } \
}

void fn_80215D04(Sc* s);

void fn_802160C0(Sc* s);

void fn_802161FC(Sc* s);

void fn_80216478(Sc* s);


extern char lbl_803CAB38[];
u8* fn_80060728(void*);
void fn_801E7938(void*, int);
#define HLP(name, off) \
void name(Sc* s) { \
    switch (s->a40) { \
    case 6: { void* w = fn_801E5640(s, 0x81, 0); if (w != NULL) fn_801E7938(w, *(int*)(fn_80060728(lbl_803CAB38) + off)); break; } \
    case 9: { void* w = fn_801E5640(s, 0x82, 0); if (w != NULL) fn_801E7938(w, *(int*)(fn_80060728(lbl_803CAB38) + off)); break; } \
    } \
    fn_80083DC4(s, (u8)s->a40); \
}



void* fn_80081050(void*, int);
void* fn_80081194(void*, int);
void fn_801E4094(void*);
extern void* lbl_8038F5C8[];
struct P58 { u8 p[0x40]; int a, b, c, d, e, f; };
P58* fn_80216744(int x);


void fn_80072ACC(int, int, int, int, int, int, int);
void fn_80216D74(void* o, int x, int y, int w, int h, int c);


void fn_80011CBC(void*, void*); extern void* lbl_8038FAA0[];
void fn_8021721C(void*);
void fn_80006EE0(void*);
void fn_8023F1A8(void*);
void fn_801E2E00(void*, int);
struct S6C { void* vt; u8 p[0x5c]; void* a60; void* a64; void* a68; };
S6C* fn_8021696C(S6C* o, int del);


class LW { public:
 virtual int v08(); virtual int v0C(void*, int); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual s16 v34(); virtual int v38(); virtual int v3C();
 virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*); virtual s16 v54(); virtual int v58(int, int, int, int, int); virtual int v5C(); virtual int v60(int);
 u32 rc;
 s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; u8 p1a[4]; s16 tx, ty; u8 c[4]; u8 p26[0x12]; u32 flags; u8 p3c[0x4e - 0x3c];
 s16 cur; s16 a50, a52, rowH; u8 p56[0x6c-0x56]; struct Slot* tbl; int a70; u8 p74[0x24]; int page; void* a9c;
};
typedef struct XY { s16 x, y; } XY;
void* fn_801E2204(void*, void*, void*);
static inline void* mp(void* o, void* r, s16 x, s16 y) { XY p; p.x = x; p.y = y; return fn_801E2204(o, r, &p); }
u32 fn_80216A1C(const LW* o);

u32 fn_80217BC4(const LW* o);


extern char lbl_80371974[];
void fn_80216F84(LW* o, void* a);

void fn_802170D8(LW* o);

void fn_801D95A0(int, int, int, int);
void fn_80217368(LW* o);

int fn_802172F8(LW* o);

extern void* lbl_8038F758[];
void* fn_80217328(LW* o);

void fn_80217638(LW* o);

void fn_801D9788(int, int, u32);
void fn_80217658(LW* o);

struct Slot { u32 a, b; void* p; };
int fn_80217220(LW* o, int i);

s16 fn_802179DC(LW* o);

void* fn_8010B228(void*);
void fn_80217ABC(const LW* o);

void fn_801D9818(int, int, int, int, int, u32);
void fn_80217C34(LW* o);

void fn_80107C80(void*, int, int, int);
void fn_802176A0(LW* o, void* a);


int fn_8028DB44(int);
void fn_800712E8(int, int, int);
void fn_8007E7E8(int);
struct Ctx { u8 p[0x2d]; u8 a2d; u8 a2e; u8 p2f[5]; int a34; struct { u8 p[8]; void* a8; }* a38; };
static inline BOOL ctxBusy(Ctx* c) { BOOL b = FALSE; if (c->a2d != 0 || c->a2e != 0) b = TRUE; return b; }
static inline void* ctxTop(Ctx* c) { return c->a34 != 0 ? c->a38->a8 : NULL; }
static inline int ctxSel(Ctx* c, void* o) { int sel = 0; if (!ctxBusy(c)) { if (ctxTop(c) == o) sel = 1; } return sel; }
void fn_80216DA0(LW* o, Ctx* c);

void fn_80218448(LW* o, Ctx* c);


void fn_800CB3A8(f32, f32, int, int, int, int, int, void*, ...);
void fn_80080ABC(f32, int);
void fn_801D8ADC(int, int, int, int);
void fn_80217CD4(LW* o, int x, int y, const char* msg, int n);


void* fn_80110BB4(void*, void*);
void fn_802185D4(LW* o, void* a);


extern void* lbl_8038F788[];
void* fn_80218B38(LW* o);

void fn_801DA350(int, int, int, u32);
void fn_80218C34(LW* o);

void fn_801DA618(int, int, int, u32);
void fn_8021A89C(LW* o);

void fn_801E2F40(void*, void*);
extern void* lbl_8038FA04[];
class LX { public:
 virtual int v08(); virtual int v0C(void*, int); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(int); virtual int v3C();
 virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*);
 u32 rc;
 s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; u8 p1a[4]; s16 tx, ty; u8 c[4]; s16 a26; u8 p28[0x54-0x28];
 s16 rowH; u8 p56[0x88-0x56]; void* a88;
};
struct WD { WF w; void* a40; };
void fn_8021A27C(LX* o);

void fn_8021A434(LW* o, void* a);

u32 fn_80218B78(const LW* o);


void fn_80111FE4(void*, void*);
void* fn_80110F08(void*);
struct C4 { u8 r, g, b, a; };
struct It { u8 p[5]; u8 fl; u8 p6[0x18]; s8 a1e, a1f, a20, a21; u8 a22[4]; };
extern const C4 lbl_804CFBDC;
#define COLK 0x80,0x80,0x80,0xff

void fn_80218A48(LW* o, It* it);


void fn_801DAE3C(int, int, int);
void fn_8021B408(LW* o);

void fn_8021CCE0(LW* o);

void fn_801DAEF4(int, int, int, int, u32);
void fn_8021CD64(LW* o);

void* fn_8021CD4C(u8* o);

u32 fn_8021CD58(u8* o);

void* fn_80077064(void*);
struct Ent12 { u32 a, b, c; };
struct H12 { u32 n; Ent12 e[1]; };
void fn_8021CCF0(u8* o, s8 k);

void memcpy(void*, const void*, u32);
void fn_8021C6DC(u8* o);

class V3C { public: virtual int v08(); virtual int v0C(void*, int); };
void fn_8021C638(V3C* o, int i);

u32 fn_8021C68C(const u8* o);

void fn_8021CBC8(u8* o);

extern void* lbl_8038F868[];
void fn_8021BFBC(void*);
struct S4C { void* vt; u8 p[0x44]; void** a48; };
S4C* fn_8021BA84(S4C* o, int del);

class V343 { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int);
};
void fn_8021BA28(V343* o, int a);

f64 fn_80295A9C(f64, f64);
#define MODK 360.0
#define ADDK 180.0f
struct A44 { u8 p[0x44]; f32 a44; };
struct S44 { u8 p[0x28]; s16 a28; u8 p2a[6]; s8 a30; int a34; f32 a38, a3c; A44* a40; };
void fn_8021C1B0(S44* o);

f32 fn_8017F68C(f32, f32, f32, f32, int);
void fn_8021C1EC(S44* o);

extern void* lbl_8038F7BC[];
void fn_8021C278(u8* t, s8 k, int n, void* par, int mode);

int fn_800CA3DC(f32, const void*, int);
void fn_80290D04(void*, int, const char*, ...);
void fn_8021CDCC(LW* o, s16 x, s16 y, const char* m, int k);

}