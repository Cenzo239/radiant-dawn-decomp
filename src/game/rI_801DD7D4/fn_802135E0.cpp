#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void* fn_80079150(u32);

class V3x { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(int); };
void fn_802135E0(V3x* o, int a) {
    o->v34();
    o->v3C(a);
}

#if TARGET_PC
FE10_PROTO void fn_801E17FC(void*, ptr32<const void>);
#else
void fn_801E17FC(void*, void*);
#endif
int fn_8012EA2C(void*, int);
u8 fn_8012E830(void*);
void* fn_8012E854(void*, int);
void* fn_8012E3A4(void*);
void fn_8007E154(void);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
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
void fn_8021363C(V18* o, void* a) {
    s16 n;
    s16 h;
    int i;
    s16 y;
    void* t;
    s16 x;
    W* w = (W*)o;
    fn_801E17FC(o, a);
    o->v18(a);
    t = *(void**)((u8*)o + 0x50);
    if (t != NULL) {
        n = 0;
        for (i = 0; i < fn_8012E830(t); i++) {
            if (fn_8012EA2C(t, i) != 0) {
                n++;
            }
        }
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(w->flags | 3));
        fn_8007E164();
        x = w->tx + (s16)(w->ix1 - w->ix0);
        y = w->ty;
        h = w->iy1 - w->iy0;
        y += (h - fn_800CB0FC(1.0f, -1)) >> 1;
        fn_800800D4(5);
        fn_80176F7C(x, y, 0, 0, n);
        fn_80080308();
    }
}

void fn_8021376C(VO0* o) {
    o->v14();
    fn_801D9064(0, 0, 0x10);
    fn_801D9064(0x90, 0, 0x10);
}

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

void* fn_8021395C(void* p, int del) {
    if (p != NULL) {
        m44dtor((P44*)p);
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void* fn_802139D8(void* p, int del) {
    if (p != NULL) {
        if (p != NULL) {
            m44dtor((P44*)p);
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

#define FREE_FN(name) \
void* name(void* p, int del) { \
    if (p != NULL && del > 0) { \
        fn_80079210(p); \
    } \
    return p; \
}
FREE_FN(fn_80213A58)
FREE_FN(fn_80213A98)

static inline s16 wW(W* w) { return w->x1 - w->x0; }
static inline s16 wH(W* w) { return w->y1 - w->y0; }
static inline s16 wH2(W* w) { s16 a = w->y0; s16 b = w->y1; return b - a; }
static inline void setI(W* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
static inline void setI2(W* w, int a, int b, int c, int d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
void fn_80213AE0(W* w) { setI2(w, 0, 0, wW(w), wH(w)); }
void fn_80213B10(W* w) { setI(w, 0x20, 0, wW(w) - 0x20, wH(w)); }

class RObj2 { public: virtual void destroy(int); int rc; };
#define REL(f) if (o->f != NULL) { RObj2* r = o->f; if (--r->rc == 0) { if (r != NULL) { r->destroy(1); } } o->f = NULL; }
struct S54 { u8 pad[0x44]; RObj2* a, *b, *c, *d, *e; };
void fn_80213E24(S54* o) {
    if (o != NULL) {
        REL(a) REL(b) REL(c) REL(d) REL(e)
        fn_801E40B0(o, 0);
    }
}

struct Wi { u8 p[0xa]; s16 x, y; u8 p2[0x32]; void* a40; u8 p3[0xc]; u8 b50; u8 p4[3]; void* a54; u8 p5[0xc]; void* a64; };
struct Sc { u8 p[0x40]; int a40; Wi* a44, *a48, *a4c, *a50, *a54; };
struct Pt { s16 x, y; };

static inline void mv(Sc* s, Wi* w, s16 x, s16 y, int f) { Pt p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void setHelp(Sc* s, char* const& str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }


#define FIND(res, id, fld) res = (Wi*)fn_801E5640(s, id, 0); if (res == NULL) { res = s->fld; fn_801E5448(s, res); }

static inline Wi* findOr(Sc* s, int id, Wi*& w0) { Wi* r = (Wi*)fn_801E5640(s, id, 0); if (r == NULL) { r = w0; fn_801E5448(s, r); } return r; }
void fn_80214704(Sc* s) {
    Wi* a = findOr(s, 0x81, s->a44);
    Wi* b; Wi* c; Wi* d;
    if (a->y != 0x1c) { Pt p; p.x = a->x; p.y = 0x1c; fn_801E459C(s, a, &p, 1); }
    a->b50 = 0;
    b = findOr(s, 0x83, s->a4c);
    if (b->x != 0x20) mv(s, b, 0x20, b->y, 0);
    b->a40 = fn_801E7A28(a);
    c = findOr(s, 0x87, s->a50);
    if (c->x != 0x12c) mv(s, c, 0x12c, c->y, 0);
    *(void**)((u8*)c + 0x50) = fn_801E7A28(a);
    d = findOr(s, 0x86, s->a54);
    if (d->x != 0x12c) mv(s, d, 0x12c, d->y, 0);
    d->a40 = fn_801E7A28(a);
    {
        Wi* t = (Wi*)fn_801E5640(s, 0x80, 0);
        t->a40 = lbl_803712F8;
        fn_801E5734(s, a);
        setHelp(s, lbl_803712F8 + 0x1a);
    }
}

int fn_80214618(void* u) {
    void* c = fn_8012E3A4(u);
    if (c != NULL) {
        switch (*(u8*)(*(u8**)((u8*)c + 0xf4) + 8)) {
        case 0:
        case 5:
            return 1;
        }
    }
    {
        int i;
        int r;
        int n = fn_8012E830(u);
        r = 0;
        for (i = 0; i < n; i++) {
            void* e = fn_8012E854(u, i);
            if (e != NULL) {
                switch (*(u8*)(*(u8**)((u8*)e + 0xf4) + 8)) {
                case 0:
                case 5:
                    if (fn_8012EA2C(u, i) != 0) {
                        r = 1;
                        goto end;
                    }
                }
            }
        }
    end:
        return r;
    }
}

void fn_80215024(Sc* s) {
    Wi* a;
    Wi* w = (Wi*)fn_801E5640(s, 0x84, 0);
    if (w->x != 0x20) mv(s, w, 0x20, w->y, 1);
    FIND(a, 0x82, a48)
    if (a->x != 0x138) mv(s, a, 0x138, a->y, 0);
    a->b50 = 0;
    {
        Wi* t = (Wi*)fn_801E5640(s, 0x80, 0);
        t->a40 = lbl_803712F8 + 0x66;
        fn_801E5734(s, a);
        setHelp(s, lbl_803712F8 + 0x7f);
    }
}

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
/* fn_80213B4C: near miss, see wip/fn_802135E0.cpp */
void fn_80213B4C(Sc* s);


extern VO0N* lbl_804CB5B8;
void fn_801E495C(void*, void*, void*, int);
void fn_801E5954(void*);
void fn_801E6B64(const char*, void*, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_801E6C44(void*, void*, p32arg);
#else
void fn_801E6C44(void*, void*, int);
#endif
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
void fn_8021491C(Sc* s) {
    Wi* a;
    Wi* b;
    Wi* c;
    Wi* d;
    void* sel;

    a = (Wi*)fn_801E5640(s, 0x81, 0);
    b = (Wi*)fn_801E5640(s, 0x83, 0);
    c = (Wi*)fn_801E5640(s, 0x87, 0);
    d = (Wi*)fn_801E5640(s, 0x86, 0);
    sel = fn_801E7A28(a);
    a->b50 = 1;
    fn_801E5954(s);
    if (sel != fn_801E7A28(a)) {
        sel = fn_801E7A28(a);
    }
    b->a40 = sel;
    *(void**)((u8*)c + 0x50) = sel;
    d->a40 = sel;
    if (!inputBlocked()) {
        u32 btn = lbl_804CB5B8->v48();
        if ((btn & 0x400) && sel != NULL) {
            if (((WV*)a)->v50(sel) == 0) {
                Pt p1 = wpos((WV*)a);
                msgAt(lbl_803712F8 + 0x2e, s, p1.x, p1.y);
            } else {
                mv2(s, a, a->x, -0x24, 1);
                mv2(s, b, -0x34, b->y, 0);
                mv2(s, c, 0x180, c->y, 0);
                mv2(s, d, 0x180, d->y, 0);
                fn_80083B78(s);
                fn_80253EE4(lbl_803712F8 + 0x46, 0.0f);
            }
        } else if ((btn & 0x2000) && sel != NULL) {
            fn_801E6C44(sel, s, 1);
            s->a40 = 6;
            fn_80083DC4(s, 0xf);
        } else if ((btn & 0x1000) && sel != NULL) {
            fn_801E6D50(sel, s);
            s->a40 = 6;
            fn_80083DC4(s, 0x10);
        } else if (btn & 0x800) {
            fn_80083DC4(s, 0x11);
            fn_80253EE4(lbl_803712F8 + 0x56, 0.0f);
        }
    }
}

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
void fn_80215B44(Sc* s) {
    N34* a; N34* b;
    a = (N34*)fn_801E5640(s, 0x84, 0);
    b = (N34*)fn_801E5640(s, 0x85, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        fn_80083DC4(s, (u8)s->a40);
        break;
    case 0x80:
        animA(s, a, 1.0f);
        animTo(s, b, 1.0f);
        fn_80083DC4(s, 0xb);
        break;
    }
}

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
#if TARGET_PC
FE10_PROTO void fn_8012E388(void*, p32arg);
#else
void fn_8012E388(void*, int);
#endif
void fn_8012E398(void*, void*);
void* fn_80085EF8(u8);
void* fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO void fn_801ABBA8(void*, ptr32<const void>, void*, int);
#else
void fn_801ABBA8(void*, const char*, void*, int);
#endif
extern u32 lbl_804CB728;

static inline void mv48(Sc* s) { s16 y2 = s->a48->y; Pt p2; p2.x = 0x18c; p2.y = y2; fn_801E495C(s, s->a48, &p2, 0); }
void fn_80215148(Sc* s) {
    void* sel;
    Wi* w;
    w = (Wi*)fn_801E5640(s, 0x84, 0);
    s->a48->b50 = 1;
    sel = fn_801E7A28(s->a48);
    fn_801E5954(s);
    if (sel != fn_801E7A28(s->a48)) {
        sel = fn_801E7A28(s->a48);
    }
    if (!inputBlocked()) {
        u32 btn = lbl_804CB5B8->v48();
        if ((btn & 0x400) && sel != NULL) {
            Pt p1 = wpos((WV*)s->a48);
            u8 k;
            f32 fx = p1.x; f32 fy = p1.y;
            if (sel == NULL || ((k = *(u8*)(*(u8**)((u8*)sel + 0xf4) + 8)) != 0 && k != 5)) {
                fn_801E6B64(lbl_803712F8 + 0x93, s, fx, fy);
            } else if (((WV*)s->a48)->v50(sel) == 0) {
                fn_801E6B64(lbl_803712F8 + 0xa8, s, fx, fy);
            } else {
                mv48(s);
                fn_80083B78(s);
                fn_80253EE4(lbl_803712F8 + 0x46, 0.0f);
            }
        } else if ((btn & 0x2000) && sel != NULL) {
            fn_801E6C44(sel, s, 1);
            s->a40 = 9;
            fn_80083DC4(s, 0xf);
        } else if ((btn & 0x1000) && sel != NULL) {
            fn_801E6D50(sel, s);
            s->a40 = 9;
            fn_80083DC4(s, 0x10);
        } else if ((btn & 0x800) && fn_801A2224(lbl_8041EB20) == 0) {
            mv2(s, w, -0x34, w->y, 0);
            mv48(s);
            {
                RObj2* r = (RObj2*)s->a48;
                if (r != NULL) {
                    if (--r->rc == 0) { if (r != NULL) r->destroy(1); }
                    s->a48 = NULL;
                }
            }
            fn_80083DC4(s, 5);
            fn_80253EE4(lbl_803712F8 + 0x56, 0.0f);
        }
    }
}

static inline u8* dlg2(const char* no, const char* yes) { return (u8*)fn_801E041C(yes, no); }
#pragma use_lmw_stmw on
/* fn_80215688: near miss, see wip/fn_802135E0.cpp */
void fn_80215688(Sc* s);


#pragma use_lmw_stmw off
void fn_80215828(Sc* s) {
    void* u = fn_801E7A28(s->a44);
    void* v = fn_801E7A28(s->a48);
    Wi* w;
    fn_801E5640(s, 0x84, 0);
    w = (Wi*)fn_801E5640(s, 0x85, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        if ((fn_8012E390(u) == NULL && fn_8012E390(v) == NULL) || fn_8012E3A4(u) == v) {
            fn_80083DC4(s, 0xd);
        } else {
            s->a40 = 0xd;
            fn_80083DC4(s, 0xc);
        }
        break;
    case 0x80:
        if (fn_8012E3A4(u) == v && !(*(u8*)&lbl_804CB728 & 8)) {
            s->a40 = 0xe;
            fn_80083DC4(s, 0xc);
        } else {
            mv2(s, w, 0x18c, w->y, 0);
            fn_80083DC4(s, 8);
        }
        break;
    }
}

void fn_80215984(Sc* s) {
    N34* a;
    N34* b;
    a = (N34*)fn_801E5640(s, 0x84, 0);
    b = (N34*)fn_801E5640(s, 0x85, 0);
    animA(s, a, 0.5f);
    animTo(s, b, 0.5f);
    {
        u8* m = (u8*)fn_801E00D0(lbl_803712F8 + 0xfa);
        m[0x24] = 1;
        fn_800D5448(m, s, 0);
    }
    setHelp(s, lbl_803712F8 + 0xe7);
}

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
void fn_80215D04(Sc* s) {
    N34* a; N34* b; void* u; void* v;
    u = fn_801E7A28(s->a44);
    v = fn_801E7A28(s->a48);
    a = (N34*)fn_801E5640(s, 0x84, 0);
    b = (N34*)fn_801E5640(s, 0x85, 0);
    animA(s, a, 0.5f);
    animTo(s, b, 0.5f);
    UNLINK(u, v)
    UNLINK(v, u)
    UNLINK2(u, v)
    UNLINK2(v, u)
    fn_8012E398(u, v);
    fn_8012E398(v, u);
    {
        s8 a1 = fn_8012E9B4(u, v);
        s8 b1 = fn_8012E9B4(v, u);
        fn_8012EC10(u, a1);
        fn_8012EC10(v, b1);
        switch (fn_8012E8BC(u, a1)) {
        case 1:
            fn_801ABBA8(fn_800D0864(lbl_803712F8 + 0x113), lbl_803712F8 + 0x125, s, 2);
            break;
        case 2:
            fn_801ABBA8(fn_800D0864(lbl_803712F8 + 0x136), lbl_803712F8 + 0x125, s, 2);
            break;
        case 3:
            fn_801ABBA8(fn_800D0864(lbl_803712F8 + 0x148), lbl_803712F8 + 0x125, s, 2);
            break;
        }
    }
}

void fn_802160C0(Sc* s) {
    N34* a = (N34*)fn_801E5640(s, 0x84, 0);
    Wi* b = (Wi*)fn_801E5640(s, 0x85, 0);
    animB(s, a, 1.0f);
    mv2(s, b, 0x18c, b->y, 0);
    fn_80083DC4(s, 8);
}

void fn_802161FC(Sc* s) {
    void* e; N34* a; void* u; void* v; N34* b;
    u = fn_801E7A28(s->a44);
    v = fn_801E7A28(s->a48);
    a = (N34*)fn_801E5640(s, 0x84, 0);
    b = (N34*)fn_801E5640(s, 0x85, 0);
    animA(s, a, 0.5f);
    animTo(s, b, 0.5f);
    if (fn_8012E390(u) != NULL) {
        int k = fn_8012E944(u, fn_8012E390(u));
        fn_8012ED88(u, k);
    }
    if (fn_8012E390(v) != NULL) {
        int k = fn_8012E944(v, fn_8012E390(v));
        fn_8012ED88(v, k);
    }
    if (fn_8012E390(u) != NULL) {
        fn_8012E388(fn_8012E3A4(u), 0);
    }
    if (fn_8012E390(v) != NULL) {
        e = *(void**)((u8*)u + 0xec);
        if (fn_8012E390(v) != e) {
            fn_8012E388(fn_8012E3A4(v), 0);
        }
    }
    fn_8012E388(u, 0);
    fn_8012E388(v, 0);
    fn_801ABBA8(fn_800D0864(lbl_803712F8 + 0x15a), lbl_803712F8 + 0x16c, s, 2);
}

void fn_80216478(Sc* s) {
    N34* a = (N34*)fn_801E5640(s, 0x84, 0);
    Wi* b = (Wi*)fn_801E5640(s, 0x85, 0);
    animB(s, a, 1.0f);
    mv2(s, b, 0x18c, b->y, 0);
    fn_80083DC4(s, 8);
}

extern char lbl_803CAB38[];
u8* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
#define HLP(name, off) \
void name(Sc* s) { \
    switch (s->a40) { \
    case 6: { void* w = fn_801E5640(s, 0x81, 0); if (w != NULL) fn_801E7938(w, *(int*)(fn_80060728(lbl_803CAB38) + off)); break; } \
    case 9: { void* w = fn_801E5640(s, 0x82, 0); if (w != NULL) fn_801E7938(w, *(int*)(fn_80060728(lbl_803CAB38) + off)); break; } \
    } \
    fn_80083DC4(s, (u8)s->a40); \
}
HLP(fn_802165B4, 0x24)
HLP(fn_8021667C, 0x28)

#if TARGET_PC
FE10_PROTO void* fn_80081050(void*, p32arg);
#else
void* fn_80081050(void*, int);
#endif
#if TARGET_PC
FE10_PROTO void* fn_80081194(void*, p32arg);
#else
void* fn_80081194(void*, int);
#endif
void fn_801E4094(void*);
extern void* lbl_8038F5C8[];
struct P58 { u8 p[0x40]; int a, b, c, d, e, f; };
P58* fn_80216744(int x) {
    P58* o;
    if (x != 0) {
        o = (P58*)fn_80081194(lbl_8038F5C8, x);
    } else {
        o = (P58*)fn_80081050(lbl_8038F5C8, x);
    }
    if (o != NULL) {
        fn_801E4094(o);
        o->a = 0; o->b = 0; o->c = 0; o->d = 0; o->e = 0; o->f = 0;
    }
    return o;
}

void fn_80072ACC(int, int, int, int, int, int, int);
void fn_80216D74(void* o, int x, int y, int w, int h, int c) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x18, 0x19, 0x4c, c);
}

void fn_80011CBC(void*, void*); extern void* lbl_8038FAA0[];
void fn_8021721C(void*);
void fn_80006EE0(void*);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
void fn_801E2E00(void*, int);
struct S6C { void* vt; u8 p[0x5c]; void* a60; void* a64; void* a68; };
S6C* fn_8021696C(S6C* o, int del) {
    if (o != NULL) {
        o->vt = lbl_8038FAA0;
        if (o->a60 != NULL) fn_80011CBC(fn_8021721C, o->a60);
        if (o->a64 != NULL) fn_80011CBC(fn_80006EE0, o->a64);
        if (o->a68 != NULL) fn_80011CBC(fn_8023F1A8, o->a68);
        fn_801E2E00(o, 0);
        if (del > 0) fn_80079210(o);
    }
    return o;
}

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
u32 fn_80216A1C(const LW* o) {
    u32 r[3]; XY p;
    s16 h = o->rowH;
    int c = ((VO0N*)o)->v34();
    int m = c * h;
    int y = m + o->ty;
    p.x = o->tx;
    p.y = y;
    return *(u32*)fn_801E2204((void*)o, r, &p);
}
u32 fn_80217BC4(const LW* o) {
    u32 r[3]; XY p;
    s16 h = o->rowH;
    int c = ((VO0N*)o)->v34();
    int m = c * h;
    int y = m + o->ty;
    p.x = 0;
    p.y = y;
    return *(u32*)fn_801E2204((void*)o, r, &p);
}

extern char lbl_80371974[];
void fn_80216F84(LW* o, void* a) {
    s16 n = o->v54();
    s16 c = o->v34();
    if (!inputBlocked()) {
        int a = ((VO0N*)lbl_804CB5B8)->v3C();
        int b = lbl_804CB5B8->v48();
        s16 old = o->cur;
        if (a & 0x800008) {
            if (c == 0) {
                if (a == b) o->cur = n - 1;
            } else {
                o->cur = old - 1;
            }
        } else if (a & 0x400004) {
            if (c == n - 1) {
                if (a == b) o->cur = 0;
            } else {
                o->cur = old + 1;
            }
        }
        if (old != o->cur) {
            fn_80253EE4(lbl_80371974 + 0x34, 0.0f);
        }
    }
}

void fn_802170D8(LW* o) { o->v24(); }
void fn_801D95A0(int, int, int, int);
void fn_80217368(LW* o) {
    o->v14();
    fn_801D95A0(0, 0, (s16)(o->x1 - o->x0), 0x10);
}
int fn_802172F8(LW* o) { return o->v34(); }
extern void* lbl_8038F758[];
void* fn_80217328(LW* o) { return lbl_8038F758[o->v34()]; }
void fn_80217638(LW* o) { if (o->a70 != 1) o->v24(); }
void fn_801D9788(int, int, u32);
void fn_80217658(LW* o) {
    o->v14();
    fn_801D9788(0, 0, o->flags);
}
struct Slot { u32 a, b; void* p; };
int fn_80217220(LW* o, int i) {
    Slot* s = o->tbl + i * 10;
    int r = 0;
    int j;
    for (j = 0; j < 10; j++) {
        if (s->p != NULL) { r = 1; break; }
        s++;
    }
    return r;
}
s16 fn_802179DC(LW* o) {
    Slot* s = o->tbl + o->page * 10;
    s16 n = 0;
    int j;
    for (j = 0; j < 10; j++) {
        if (s->p != NULL) n++;
        s++;
    }
    return n;
}
void* fn_8010B228(void*);
void
#if TARGET_PC
*
#endif
fn_80217ABC(const LW* o) {
    Slot* s = o->tbl + o->page * 10;
    s16 c = ((LW*)o)->v34();
    s16 n = 0;
    int j;
    for (j = 0; j < 10; j++, s++) {
        if (s->p != NULL && n++ == c) break;
    }
#if TARGET_PC
    return fn_8010B228(s->p);
#else
    fn_8010B228(s->p);
#endif
}
void fn_801D9818(int, int, int, int, int, u32);
void fn_80217C34(LW* o) {
    o->v14();
    {
        s16 w = o->x1 - o->x0;
        s16 n = o->v54();
        fn_801D9818(0, 0, w, o->v34(), n, o->flags);
    }
}
void fn_80107C80(void*, int, int, int);
void fn_802176A0(LW* o, void* a) {
    o->v30();
    o->v18(a);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    { void* m = *(void**)((u8*)o + 0x40); int x = o->tx; int y = o->ty; if (m != NULL) {
        fn_80107C80(m, 1, x, y);
    } }
}

int fn_8028DB44(int);
void fn_800712E8(int, int, int);
void fn_8007E7E8(int);
struct Ctx { u8 p[0x2d]; u8 a2d; u8 a2e; u8 p2f[5]; int a34; struct { u8 p[8]; void* a8; }* a38; };
static inline BOOL ctxBusy(Ctx* c) { BOOL b = FALSE; if (c->a2d != 0 || c->a2e != 0) b = TRUE; return b; }
static inline void* ctxTop(Ctx* c) { return c->a34 != 0 ? c->a38->a8 : NULL; }
static inline int ctxSel(Ctx* c, void* o) { int sel = 0; if (!ctxBusy(c)) { if (ctxTop(c) == o) sel = 1; } return sel; }

void fn_80216DA0(LW* o, Ctx* c) {
    s16 w, h, tx;
    int sel;
    s16 ax;
    s16 y;
    s16 hh;
    o->v18(c);
    w = o->ix1 - o->ix0;
    h = o->rowH;
    {
        int k = ((VO0N*)o)->v34();
        int m = k * h;
        ax = o->a50;
        tx = o->tx;
        y = m + o->ty;
    }
    {
    s16 ay;
    if (ax == -0x8000 || (ay = o->a52) == -0x8000 || (fn_8028DB44(ax - tx) <= 1 && fn_8028DB44(ay - y) <= 1)) {
        o->a50 = tx;
        o->a52 = y;
    } else {
        o->a50 = (ax + tx + 1) >> 1;
        o->a52 = (y + o->a52 + 1) >> 1;
    }
    }
    if (((VO0N*)o)->v3C() != 0) {
        sel = 0; if (!ctxBusy(c)) { if (ctxTop(c) == o) sel = 1; }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        {
            hh = o->rowH;
            fn_800712E8(o->a50, o->a52 + ((hh - fn_800CB0FC(1.0f, -1)) >> 1), sel);
        }
        fn_8007E154();
        fn_8007E720(3.0f);
        fn_8007E164();
        o->v58((s16)(tx - o->tx), y, w, h, sel);
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

void fn_80218448(LW* o, Ctx* c) {
    s16 hh;
    s16 h;
    int sel;
    s16 ax, ay, y;
    o->v18(c);
    h = o->rowH;
    { int k = ((VO0N*)o)->v34(); y = k * h; }
    ax = o->a50;
    if (ax == -0x8000 || (ay = o->a52) == -0x8000 || (fn_8028DB44(ax) <= 1 && fn_8028DB44(ay - y) <= 1)) {
        o->a50 = 0;
        o->a52 = y;
    } else {
        o->a50 = (ax + 1) >> 1;
        o->a52 = (y + o->a52 + 1) >> 1;
    }
    if (((VO0N*)o)->v3C() != 0) {
        sel = ctxSel(c, o);
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        hh = o->rowH;
        { int d = (hh - fn_800CB0FC(1.0f, -1)) >> 1; fn_800712E8(o->a50, d + o->a52 + 8, sel); }
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

void fn_800CB3A8(f32, f32, int, int, int, int, int, void*, ...);
void fn_80080ABC(f32, int);
void fn_801D8ADC(int, int, int, int);
void fn_80217CD4(LW* o, int x, int y, const char* msg, int n) {
    s16 h = o->rowH;
    s16 w = (s16)(o->ix1 - o->ix0) - 0x65 - o->tx * 2;
    int t = (h - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    t = (int)y + (int)t;
    fn_800CB3A8(1.0f, 0.0f, (s16)(x + 8), (s16)t, 0x1d, 1, 0, fn_800D0864(msg));
    fn_800800D4(5);
    fn_80080ABC(2.0f, 1);
    fn_80176F7C(x + w - 8, t, 0, 0, n);
    fn_80080308();
    fn_801D8ADC(x, (s16)(y + o->rowH - 10), w, 0x10);
}

void* fn_80110BB4(void*, void*);
void fn_802185D4(LW* o, void* a) {
    s16 c = o->v34();
    fn_80216F84(o, a);
    if (c != o->v34()) {
        Slot* s = o->tbl + o->page * 10;
        s16 k = o->v34();
        int j;
        s16 n = 0;
        for (j = 0; j < 10; j++, s++) {
            if (s->p != NULL && n++ == k) break;
        }
        fn_80110BB4(&o->a70, fn_8010B228(s->p));
        o->v50(&o->a70);
        *(void**)((u8*)o->a9c + 0x40) = &o->a70;
    }
}

extern void* lbl_8038F788[];
void* fn_80218B38(LW* o) { return lbl_8038F788[o->v34()]; }
void fn_801DA350(int, int, int, u32);
void fn_80218C34(LW* o) {
    o->v14();
    fn_801DA350(0, 0, (s16)(o->x1 - o->x0), o->flags);
}
void fn_801DA618(int, int, int, u32);
void fn_8021A89C(LW* o) {
    o->v14();
    fn_801DA618(0, 0, (s16)(o->x1 - o->x0), o->flags);
}
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
void fn_8021A27C(LX* o) {
    setI((W*)o, 4, 4, wW((W*)o) - 4, wH((W*)o) - 4);
    o->tx = 0x12;
    o->ty = 8;
    o->rowH = 0x1c;
    o->v38(0);
    o->v50(0);
    if (o->a88 != NULL) {
        o->v0C(o->a88, 0);
    }
    {
        WD* d = (WD*)fn_80079150(0x44);
        if (d != NULL) {
            s16 a = o->a26;
            wfInit(&d->w, -4, -0x1c, 0x100, 4, 0x104, 0x20, a - 5, 0x10);
            d->w.vt = lbl_8038FA04;
            d->a40 = 0;
            ((VO0N*)d)->v2C();
        }
        o->a88 = d;
        fn_801E2F40(o, d);
    }
}

void fn_8021A434(LW* o, void* a) {
    *(void**)&o->a70 = a;
    o->v50(a);
    *(int*)((u8*)*(void**)((u8*)o + 0x88) + 0x40) = o->a70;
}
u32 fn_80218B78(const LW* o) {
    u32 r[3]; XY p;
    s16 h = o->rowH;
    s16 c = ((LW*)o)->v34();
    s16 x = o->tx;
    s16 y = o->ty;
    switch (c) {
    case 0: case 1: case 2: case 3:
        y += c * h;
        break;
    case 4:
        y = 0x98;
        break;
    case 5:
        y = 0xc4;
        break;
    case 6:
        y = 0xe5;
        break;
    }
    p.x = x;
    p.y = y;
    return *(u32*)fn_801E2204((void*)o, r, &p);
}

void fn_80111FE4(void*, void*);
void* fn_80110F08(void*);
struct C4 { u8 r, g, b, a; };
struct It { u8 p[5]; u8 fl; u8 p6[0x18]; s8 a1e, a1f, a20, a21; u8 a22[4]; };
extern const C4 lbl_804CFBDC;
#define COLK 0x80,0x80,0x80,0xff
void fn_80218A48(LW* o, It* it) {
    It* old = *(It**)&o->a70;
    if (old != NULL) old->fl &= ~0x20;
    *(It**)&o->a70 = it;
    if (!(it->fl >> 5 & 1)) {
        fn_80111FE4(*(It**)&o->a70, fn_80110F08(it));
        (*(It**)&o->a70)->a1e = 0;
        (*(It**)&o->a70)->a1f = 0;
        (*(It**)&o->a70)->a20 = 0;
        (*(It**)&o->a70)->a21 = 0;
        {
            It* q;
            C4 c = {COLK};
            q = *(It**)&o->a70;
            q->a22[0] = c.r;
            q->a22[1] = c.g;
            q->a22[2] = c.b;
            q->a22[3] = c.a;
        }
        (*(It**)&o->a70)->fl |= 0x20;
    }
    o->v50(*(It**)&o->a70);
    *(int*)((u8*)*(void**)((u8*)o + 0x1b8) + 0x40) = o->a70;
}

void fn_801DAE3C(int, int, int);
void fn_8021B408(LW* o) { o->v14(); fn_801DAE3C(0, 0, 0x10); }
void fn_8021CCE0(LW* o) { o->v24(); }
void fn_801DAEF4(int, int, int, int, u32);
void fn_8021CD64(LW* o) {
    o->v14();
    fn_801DAEF4(0, 0, (s16)(o->x1 - o->x0), (s16)(o->y1 - o->y0), o->flags);
}
void* fn_8021CD4C(u8* o) { return fn_800D0864(**(const char***)(o + 0x44)); }
u32 fn_8021CD58(u8* o) { return *(u32*)(o + 0x44) + 4; }
void* fn_80077064(void*);
struct Ent12 { u32 a, b, c; };
struct H12 { u32 n; Ent12 e[1]; };
void fn_8021CCF0(u8* o, s8 k) {
    u8* d = (u8*)fn_80077064(lbl_80371974 + 0x17d) + 4;
    o[0x40] = k;
    *(u8**)(o + 0x44) = d + k * 0xc;
}
void memcpy(void*, const void*, u32);
void fn_8021C6DC(u8* o) { memcpy((u8*)lbl_803CAB38 + 0x94, o + 0x62, 6); }
class V3C { public: virtual int v08(); virtual int v0C(void*, int); };
void fn_8021C638(V3C* o, int i) {
    void** s = (void**)o + 0x13 + i;
    if (*s != NULL) {
        o->v0C(*s, 0);
        *s = NULL;
    }
}
u32 fn_8021C68C(const u8* o) {
    u32 r; XY p;
    p.y = *(s16*)(o + 0x20) + 0x5b;
    p.x = *(s16*)(o + 0x1e) + *(s16*)(o + 0x6a) * 0x78 + 0x3c;
    return *(u32*)fn_801E2204((void*)o, &r, &p);
}
void fn_8021CBC8(u8* o) {
    if (!inputBlocked() && o[0x60] == 1) {
        int a = ((VO0N*)lbl_804CB5B8)->v3C();
        int b = lbl_804CB5B8->v48();
        s16 old = *(s16*)(o + 0x6a);
        if (a & 0x100001) {
            if (old > 0) {
                *(s16*)(o + 0x6a) = old - 1;
            } else {
                if (a == b) *(s16*)(o + 0x6a) = 4;
            }
        } else if (a & 0x200002) {
            if (old < 4) {
                *(s16*)(o + 0x6a) = old + 1;
            } else {
                if (a == b) *(s16*)(o + 0x6a) = 0;
            }
        }
        if (old != *(s16*)(o + 0x6a)) {
            fn_80253EE4(lbl_80371974 + 0x34, 0.0f);
        }
    }
}
extern void* lbl_8038F868[];
void fn_8021BFBC(void*);
struct S4C { void* vt; u8 p[0x44]; void** a48; };
S4C* fn_8021BA84(S4C* o, int del) {
    if (o != NULL) {
        o->vt = lbl_8038F868;
        if (o->a48 != NULL) {
            *o->a48 = NULL;
            fn_80011CBC(fn_8021BFBC, o->a48);
        }
        if (del > 0) fn_80079210(o);
    }
    return o;
}
class V343 { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int);
};
void fn_8021BA28(V343* o, int a) { o->v30(); o->v34(a); }
f64 fn_80295A9C(f64, f64);
#define MODK 360.0
#define ADDK 180.0f
struct A44 { u8 p[0x44]; f32 a44; };
struct S44 { u8 p[0x28]; s16 a28; u8 p2a[6]; s8 a30; int a34; f32 a38, a3c; A44* a40; };
void fn_8021C1B0(S44* o) {
    f32 v = o->a3c;
    A44* t = o->a40;
    t->a44 = fn_80295A9C(v, MODK);
}
f32 fn_8017F68C(f32, f32, f32, f32, int);
/* fn_8021C1EC: near miss, see wip/fn_802135E0.cpp */
void fn_8021C1EC(S44* o);

extern void* lbl_8038F7BC[];
/* fn_8021C278: near miss, see wip/fn_802135E0.cpp */
void fn_8021C278(u8* t, s8 k, int n, void* par, int mode);

int fn_800CA3DC(f32, const void*, int);
void fn_80290D04(void*, int, const char*, ...);

void fn_8021CDCC(LW* o, s16 x, s16 y, const char* m, int k) {
    char buf[0x40];
    int fh;
    s16 w = (s16)(o->ix1 - o->ix0) - o->tx * 2;
    fh = (0x1b - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    if (k > 0) {
        fn_80290D04(buf, 0x40, lbl_80371974 + 0x18d, fn_800D0864(m), 4, k);
    } else {
        fn_80290D04(buf, 0x40, lbl_80371974 + 0x19c, fn_800D0864(m));
    }
    {
        int tw = fn_800CA3DC(1.0f, buf, -1);
        fn_800CB3A8(1.0f, 0.0f, (s16)(x + ((w - tw) >> 1)), (s16)(y + fh), 1, 1, 0, buf);
    }
}
}
