/* Near misses, snapshot of the batch before pruning:
   fn_8021D17C: 12 of 20 words differ
   fn_8021D964: 26 of 42 words differ
   fn_8021EA80: 68 of 90 words differ
   fn_802228B8: 3 of 25 words differ
   Each function also exists in the live file unless listed here. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void fn_801E2E00(void*, int);
void fn_80011CBC(void*, void*);
void fn_8021721C(void*);
void fn_80006EE0(void*);
void fn_8023F1A8(void*);
void fn_80111C24(void*, int);
void* fn_801E2204(void*, void*, void*);
void fn_8007E154(void);
void fn_8007E174(int, u32);
void fn_8007E164(void);
extern void* lbl_8038FAA0[];

struct W {
    void* vt;
    int rc;
    s16 id;
    s16 x0, y0, x1, y1;
    s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c;
    s16 tx, ty;
};
static inline s16 wW(W* w) { return w->x1 - w->x0; }
static inline s16 wH(W* w) { return w->y1 - w->y0; }
static inline void setI2(W* w, int a, int b, int c, int d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
static inline void setI(W* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }

#define FREE_FN(name) \
void* name(void* p, int del) { \
    if (p != NULL && del > 0) { \
        fn_80079210(p); \
    } \
    return p; \
}

void fn_8021D0BC(W* w) {
    setI(w, 4, 4, wW(w) - 4, wH(w) - 4);
    w->tx = 0;
    w->ty = 0;
}
int fn_8021D108(u8* o) { return *(s16*)(o + 0x4e); }
u8 fn_8021D110(u8* o) { return o[0x4c]; }
int fn_8021D118(u8* o) { return *(s16*)(o + 0x56); }
void fn_8021D120(W* w) {
    setI(w, 10, 3, wW(w) - 10, wH(w) - 3);
    w->tx = 6;
    w->ty = 1;
}
int fn_8021D174(u8* o) { return *(s16*)(o + 0x74); }
void fn_8021D17C(W* w) {
    int h = w->y1 - w->y0;
    int ww = w->x1 - w->x0;
    setI2(w, 0, 0, ww, h);
    w->tx = 0;
    w->ty = 0;
    w->a1a = (s16)ww >> 1;
    w->a1c = (s16)h >> 1;
}
void fn_8021D1CC(W* w) {
    setI(w, 3, 3, wW(w) - 3, wH(w) - 3);
    w->tx = 0xc;
    w->ty = 0xe0;
}
FREE_FN(fn_8021D21C)
extern char lbl_8038FB00[];
char* fn_8021D25C(void) { return lbl_8038FB00; }
void* fn_8021D268(void* p, int del) {
    if (p != NULL) {
        fn_801E2E00(p, 0);
        if (del > 0) fn_80079210(p);
    }
    return p;
}
void fn_8021D2C0(W* w) {
    setI2(w, 0, 0, wW(w), wH(w));
    w->tx = 0x20;
    w->ty = 0;
}
FREE_FN(fn_8021D2FC)
int fn_8021D33C(void) { return 0; }
void* fn_8021D344(u8* o) { return o + 0x50; }
struct XY { s16 x, y; };
void fn_8021D34C(u8* o, const XY* p) { *(XY*)(o + 0x50) = *p; }
void fn_8021D360(u8* o, s16 v) { *(s16*)(o + 0x4e) = v; }
struct S6C { void* vt; u8 p[0x5c]; void* a60; void* a64; void* a68; };
static inline void s6cBody(S6C* o) {
    o->vt = lbl_8038FAA0;
    if (o->a60 != NULL) fn_80011CBC(fn_8021721C, o->a60);
    if (o->a64 != NULL) fn_80011CBC(fn_80006EE0, o->a64);
    if (o->a68 != NULL) fn_80011CBC(fn_8023F1A8, o->a68);
    fn_801E2E00(o, 0);
}
S6C* fn_8021D368(S6C* o, int del) {
    if (o != NULL) {
        if (o != NULL) s6cBody(o);
        if (del > 0) fn_80079210(o);
    }
    return o;
}
int fn_8021D41C(void) { return 7; }
void fn_8021D424(u8* o, s16 v) { *(s16*)(o + 0x74) = v; }
S6C* fn_8021D628(S6C* o, int del) {
    if (o != NULL) {
        fn_80111C24((u8*)o + 0x70, -1);
        if (o != NULL) {
            s6cBody(o);
        }
        if (del > 0) fn_80079210(o);
    }
    return o;
}
FREE_FN(fn_8021D6EC)
S6C* fn_8021D72C(S6C* o, int del) {
    if (o != NULL) {
        if (o != NULL) s6cBody(o);
        if (del > 0) fn_80079210(o);
    }
    return o;
}
struct WX { W w; u8 p[0x5a - sizeof(W)]; };
void fn_8021D8A0(u8* o) {
    W* w = (W*)o;
    setI(w, 0, 0, wW(w), wH(w));
    w->tx = 0x130;
    w->ty = 0x22;
    *(s16*)(o + 0x5a) = 0xc1;
    *(s16*)(o + 0x5c) = 0x1c;
    *(s16*)(o + 0x5e) = 0;
    *(s16*)(o + 0x82) = 0xc1;
    *(s16*)(o + 0x84) = 0x66;
    *(s16*)(o + 0x86) = 0;
    *(s16*)(o + 0xaa) = 0x61;
    *(s16*)(o + 0xac) = 0x41;
    *(s16*)(o + 0xae) = 0;
    *(s16*)(o + 0xd2) = 0x120;
    *(s16*)(o + 0xd4) = 0x41;
    *(s16*)(o + 0xd6) = 0;
    *(s16*)(o + 0xfa) = 0x184;
    *(s16*)(o + 0xfc) = 0x4f;
    *(s16*)(o + 0xfe) = 0;
}
u32 fn_8021DA50(void* o) {
    u32 r; XY p;
    p.x = 0xc1;
    p.y = 0x41;
    return *(u32*)fn_801E2204(o, &r, &p);
}
void fn_801DBDF0(int, int, u32);
void fn_801DC2B0(int, int, int, int, int);
void fn_801DC7B0(int, int, int, int, int);
void fn_801DC220(int, int, int);
class VW : public VO0N { };
void fn_8021DA8C(VO0N* o) {
    o->v14();
    fn_801DBDF0(0, 0, *(u32*)((u8*)o + 0x38));
}
void fn_8021E6CC(VO0N* o) {
    o->v14();
    fn_801DC2B0(0, 0, (s16)(((W*)o)->x1 - ((W*)o)->x0), (s16)(((W*)o)->y1 - ((W*)o)->y0), 0x10);
}
void fn_8021EA18(VO0N* o) {
    o->v14();
    fn_801DC7B0(0, 0, (s16)(((W*)o)->x1 - ((W*)o)->x0), (s16)(((W*)o)->y1 - ((W*)o)->y0), 0x10);
}
void fn_8021ECC8(VO0N* o) {
    o->v14();
    fn_801DC220(0, 0, 0x10);
}
class V343 { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int);
};
void fn_8021F084(V343* o, int a) { o->v30(); o->v34(a); }
FREE_FN(fn_8021F2CC)
void fn_8021F30C(W* w) {
    setI2(w, 0, 0, wW(w), wH(w));
    w->tx = 0x20;
    w->ty = 0;
}
FREE_FN(fn_8021F348)
void fn_8021F388(W* w) {
    setI(w, 3, 3, wW(w) - 3, wH(w) - 3);
    w->tx = 0x18;
    w->ty = 6;
}
FREE_FN(fn_8021F3D8)

f32 fn_80120524(void*, int n);
f32 fn_8021DA10(void* a, void* b) {
    f32 v;
    if (b == NULL) {
        v = 0.0f;
    } else {
        v = fn_80120524(a, (int)b);
        if (v < 1.0f) v = 1.0f;
    }
    return v;
}

void fn_8021F418(W* w) {
    setI(w, 3, 3, wW(w) - 3, wH(w) - 3);
    w->tx = 0x18;
    w->ty = 6;
}
FREE_FN(fn_8021F468)
void fn_80220DA0(void) {}

void* fn_801E5640(void*, int, int);
void* fn_801E041C(const char*, const char*);
void* fn_800D5448(void*, void*, int);
void fn_800D0AE4(int, int);
void fn_801E4F50(void*, void*, int);
void fn_801E5558(void*, void*, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
extern u8 lbl_803CA870[0x130];
extern char lbl_80371CCC[];
struct Sc2 { u8 p[0x40]; u8 a40; u8 p41[3]; int a44; void* a48; void* a4c; void* a50; void* a54; struct { u8 p[0x40]; void* a40; f32 a44; int a48; }* a58; };
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
static inline void setHelp(void* s, const char* const& str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }

void fn_80220DA4(Sc2* s) {
    Wi* t = (Wi*)fn_801E5640(s, 0x80, 0);
    fn_800D0AE4(0, s->a58->a48);
    t->a40 = lbl_80371CCC + 0xaf;
    {
        u8* m = (u8*)fn_801E041C(0, 0);
        *(s16*)(m + 8) = 0x180;
        *(s16*)(m + 0xa) = 0x1b;
        m[0x24] = 1;
        fn_800D5448(m, s, 0);
    }
    setHelp(s, lbl_80371CCC + 0xcb);
}
void fn_80220E5C(Sc2* s) {
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        fn_801E4F50(s, s->a54, 0);
        fn_801E4F50(s, s->a48, 0);
        fn_801E4F50(s, s->a4c, 0);
        fn_801E4F50(s, s->a50, 0);
        fn_801E4F50(s, s->a58, 0);
        {
            void* h = fn_801E5640(s, -0x1000, 0);
            if (h != NULL) fn_801E5558(s, h, 0);
        }
        break;
    case 0x80:
        fn_80083DC4(s, 7);
        break;
    }
}
extern char lbl_803CAB38[];
u8* fn_80060728(void*);
void fn_801E7938(void*, int);
#define HLP5(name, off) \
void name(Sc2* s) { \
    void* w = fn_801E5640(s, 0x81, 0); \
    switch (s->a40) { \
    case 5: \
        if (w != NULL) fn_801E7938(w, *(int*)(fn_80060728(lbl_803CAB38) + off)); \
    } \
    fn_80083DC4(s, s->a40); \
}
HLP5(fn_80221DBC, 0x24)
HLP5(fn_80221E3C, 0x28)

void* fn_80081050(void*, int);
void* fn_80081194(void*, int);
void fn_801E4094(void*);
extern void* lbl_8038FC40[];
struct P5C { u8 p[0x40]; u8 a40; int b, c, d, e, f, g; };
static inline P5C* mk5C(int x) {
    P5C* o;
    if (x != 0) {
        o = (P5C*)fn_80081194(lbl_8038FC40, x);
    } else {
        o = (P5C*)fn_80081050(lbl_8038FC40, x);
    }
    if (o != NULL) {
        fn_801E4094(o);
        o->a40 = 0; o->b = 0; o->c = 0; o->d = 0; o->e = 0; o->f = 0; o->g = 0;
    }
    return o;
}
P5C* fn_80221EBC(int x) { return mk5C(x); }
P5C* fn_80221F44(int x) {
    P5C* o = mk5C(x);
    fn_80083DC4(o, 0xd);
    return o;
}
f32 fn_8017F68C(f32, f32, f32, f32, int);
struct S38 { u8 p[0x30]; u8* a30; int a34; };
void fn_80221FD8(S38* o) {
    int t = ++o->a34;
    if (t >= 0x1e) {
        o->a34 = 0;
        *(int*)(o->a30 + 0x64) = 0;
        fn_80083B78(o);
    } else {
        *(f32*)(o->a30 + 0x6c) = fn_8017F68C(1.0f, 0.0f, (f32)t, 30.0f, 5);
    }
}
int fn_80120378(void*);
f32 fn_80062850(void*);
int fn_8021FEC8(void* o) {
    int r = 0;
    if (fn_80120378(o) > 0) {
        f32 a = fn_8021DA10(o, (void*)1);
        if (fn_80062850(lbl_803CAB38) >= a) r = 1;
    }
    return r;
}
void fn_8002BCC4(void*);
int fn_80058718(void);
void fn_80186E4C(void*, void*);
void fn_80186EEC(void*, void*);
extern char lbl_803C8E80[];
void fn_80220FD4(void* a) {
    fn_8002BCC4(lbl_803C8E80);
    if (*(u32*)(lbl_803C8E80 + 0x15ec) & 0x10) {
        if (fn_80058718() != 0) {
            fn_80186EEC(*(void**)lbl_803CA870, a);
        } else {
            fn_80186E4C(*(void**)lbl_803CA870, a);
        }
    }
}
int fn_8011B8A4(void*);
void fn_8007E164x(void);
void fn_801080CC(void*, int, int, int, int);
struct ItemRef { void* p; u8 a; bool b; };
class V3018 { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*);
};
struct WZ { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c; s16 tx, ty; u8 p22[0x16]; u32 flags; u8 p3c[4]; void* a40; u8 p44[4]; void* a48; };
static inline int isZ(u8 v) { return v == 0; }
#define DRAWREF(name, fld) \
void name(V3018* o, void* a) { \
    WZ* w = (WZ*)o; \
    ItemRef r; \
    o->v30(); \
    o->v18(a); \
    fn_8007E154(); \
    fn_8007E174(0, (u16)(w->flags | 3)); \
    fn_8007E164(); \
    { int x = w->tx; int y = w->ty; \
    r.p = w->fld; \
    r.a = 2; \
    r.b = 0; \
    if (r.p != NULL) r.b = *((u8*)r.p + 0x20) == 0; \
    fn_801080CC(&r, 1, x, y, 0); } \
    o->v34(a); \
}
DRAWREF(fn_8021E8CC, a40)
DRAWREF(fn_8021EBF0, a48)

static inline f32 uc2(void* a, int b) {
    f32 v = fn_80120524(a, b);
    if (v < 1.0f) v = 1.0f;
    return v;
}
static inline f32 unlockCost(void* a, int b) {
    f32 v;
    if (b == 0) {
        v = 0.0f;
    } else {
        v = uc2(a, b);
    }
    return v;
}
struct S4C2 { u8 p[0x40]; void* a40; u8 p44[4]; int a48; };
bool fn_8021D964(const S4C2* o) {
    int n = o->a48;
    bool r = fn_80120378(o->a40) - n > 0;
    if (r) {
        f32 c = unlockCost(o->a40, n + 1);
        r = fn_80062850(lbl_803CAB38) >= c;
    }
    return r;
}
extern "C" double __fabs(double);
struct S48 { u8 p[0x40]; f32 a40; u8* a44; };
bool fn_8021E9A4(const S48* o) {
    int n = fn_8011B8A4(o->a44 + 0x12c); f32 a = o->a40; return (f32)__fabs((f32)n - a) >= 1.1920929e-07f;
}
extern char lbl_80371B80[];
int fn_8024F92C(const char*);
void fn_80255060(const char*, f32);
void fn_80253EE4(const char*, f32);
void* fn_80127A90(void*);
void fn_801C6D94(void*, f32, f32, f32);
static inline void sfxLoop(const char* s) {
    if ((s8)fn_8024F92C(s) < 0) fn_80253EE4(s, 0.0f);
}
void fn_8021EA80(V3018* o0, void* a) {
    S48* o = (S48*)o0;
    f32 t;
    o0->v18(a);
    {
    int n = fn_8011B8A4(o->a44 + 0x12c);
    f32 c = o->a40;
    t = (f32)n;
    if (c < t) {
        o->a40 += 0.2f;
        if (o->a40 > t) o->a40 = t;
        sfxLoop(lbl_80371B80 + 0xb1);
    } else if (c > t) {
        o->a40 -= 0.2f;
        if (o->a40 < t) o->a40 = t;
        sfxLoop(lbl_80371B80 + 0xb1);
    } else {
        fn_80255060(lbl_80371B80 + 0xb1, 0.0f);
    }
    }
    {
        f32 z = o->a40;
        int x = 0x41; int y = 0x2c;
        fn_801C6D94(fn_80127A90(o->a44), x, y, z);
    }
}

int fn_8011B680(void*, int);
void fn_8011B32C(void*, int);
void fn_8011A36C(void*);
void fn_8011AD1C(void*, int, int, int);
u8 fn_8011AB30(void*);
void fn_801E2E00(void*, int);
struct Pan { u8 p[0x5c]; u8* a5c; int a60; int a64; s16 a68; u8 p6a[2]; f32 a6c; };
struct Tw { u8 p[0x30]; Pan* a30; int a34; int a38; };
static inline void twOff(Tw* o) {
    u8* u = o->a30->a5c;
    if (fn_8011B680(u + 300, o->a38) != 0) {
        fn_8011B32C(u + 300, o->a38);
        fn_8011A36C(u + 300);
    }
}
static inline void twOn(Tw* o) {
    u8* u = o->a30->a5c;
    if (fn_8011B680(u + 300, o->a38) == 0) {
        fn_8011AD1C(u + 300, o->a38, 2, 0);
    }
}
void fn_80222064(Tw* o) { twOff(o); }
static inline int twLt(Tw* o) {
    s16 c = o->a30->a68;
    return c < fn_8011AB30(o->a30->a5c + 300);
}
int fn_802220C4(Tw* o) { return twLt(o); }
void fn_80222114(Tw* o) {
    int t = ++o->a34;
    if (t >= 0x1e) {
        o->a34 = 0;
        o->a30->a64 = 1;
        o->a30->a6c = 1.0f;
        twOff(o);
        fn_80083B78(o);
    } else {
        o->a30->a6c = fn_8017F68C(1.0f, 0.0f, (f32)t, 30.0f, 5);
    }
}
void fn_802221EC(Tw* o) {
    o->a34 = 0;
    o->a30->a64 = 2;
    o->a30->a6c = 1.0f;
}
void fn_80222210(Tw* o) {
    twOff(o);
    o->a30->a64 = 0;
}
void fn_8022227C(Tw* o) {
    int t = ++o->a34;
    if (t >= 0x1e) {
        o->a34 = 0;
        o->a30->a64 = 0;
        fn_80083B78(o);
    } else {
        o->a30->a6c = fn_8017F68C(0.0f, 1.0f, (f32)t, 30.0f, 5);
    }
}
void fn_80222308(Tw* o) { twOn(o); }
void fn_80222368(Tw* o) {
    int t = ++o->a34;
    if (t >= 0x1e) {
        o->a34 = 0;
        o->a30->a64 = 2;
        o->a30->a6c = 0.0f;
        twOn(o);
        fn_80083B78(o);
    } else {
        o->a30->a6c = fn_8017F68C(0.0f, 1.0f, (f32)t, 30.0f, 5);
    }
}
void fn_80222440(Tw* o) {
    o->a34 = 0;
    if (twLt(o)) {
        o->a30->a64 = 1;
    } else {
        o->a30->a64 = 2;
    }
    o->a30->a6c = 0.0f;
}
void fn_802224D0(Tw* o) {
    twOn(o);
    o->a30->a64 = 0;
}
void* fn_8022253C(void* p, int del) {
    if (p != NULL) {
        fn_801E2E00(p, 0);
        if (del > 0) fn_80079210(p);
    }
    return p;
}
void fn_80222594(W* w) {
    setI(w, 2, 5, wW(w) - 2, wH(w) - 5);
    w->tx = 0x18;
    w->ty = 4;
}
struct WL { u8 p[0x1e]; s16 tx, ty; u8 p22[0x50 - 0x22]; s16 cur; u8 p52[6]; s16 rowH; u8 p5a[2]; u8* a5c; };
u32 fn_802228B8(const WL* o) {
    u32 r; XY p;
    s16 y, x;
    if (o->cur < 0) {
        y = 0;
        x = 0;
    } else {
        x = o->tx;
        y = o->cur * o->rowH + o->ty;
    }
    p.x = x;
    p.y = y;
    return *(u32*)fn_801E2204((void*)o, &r, &p);
}
void fn_80222A10(WL* o, u8* u) {
    o->a5c = u;
    { bool z = fn_8011AB30(u + 300) == 0; o->cur = -z; }
}
extern void* lbl_8038FDC8[];
void fn_80222A58(WL* o, int k, int par) {
    Tw* t = (Tw*)fn_80081194(lbl_8038FDC8, par);
    *(s16*)((u8*)o + 0x68) = fn_8011AB30(o->a5c + 300);
    *(WL**)&t->a30 = o;
    t->a38 = k;
    fn_80083DC4(t, 0);
}
struct F7C { u8 p[0x78]; u8 (*f)(void*, void*); void* arg; };
u32 fn_80222C18(F7C* o, void* a) {
    u32 r = 1;
    if (o->f != NULL) {
        r = o->f(a, o->arg) != 0;
    }
    return r;
}
struct F84 { u8 p[0x80]; u8 (*f)(void*, void*); void* arg; };
u32 fn_80223B30(F84* o, void* a) {
    u32 r = 1;
    if (o->f != NULL) {
        r = o->f(a, o->arg) != 0;
    }
    return r;
}
void fn_80072ACC(int, int, int, int, int, int, int);
void fn_80222E08(void* o, int x, int y, int w, int h, int c) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x18, 0x19, 0x4c, c);
}
void fn_80223C60(void* o, int x, int y, int w, int h, int c) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, c);
}
void fn_802236C8(VO0N* o) { o->v24(); }
void fn_802248A4(VO0N* o) { o->v24(); }
void fn_801D7014(int, int, int, int, u32);
void fn_80223C8C(VO0N* o) {
    o->v14();
    fn_801D7014(0, 0, (s16)(((W*)o)->x1 - ((W*)o)->x0), (s16)(((W*)o)->y1 - ((W*)o)->y0), *(u32*)((u8*)o + 0x38));
}
int fn_80224C9C(void) { return 5; }
s16 fn_80224CA4(const u8* o) {
    return (s16)(*(s16*)(o + 0x16) - *(s16*)(o + 0x12)) / *(s16*)(o + 0x60);
}
void fn_80224CC4(void) {}
void fn_80224CC8(void) {}
struct LN { LN* prev; LN* next; void* val; };
struct LS { int size; LN* prev; LN* next; };
static inline void lsClear(LS* l) {
    LN* p = l->next;
    LN* e = (LN*)&l->prev;
    if (p != e) {
        LN* last = e->prev;
        p->prev->next = last->next;
        last->next->prev = p->prev;
        while (p != e) {
            LN* t = p;
            p = p->next;
            fn_80079210(t);
            l->size--;
        }
    }
}
void fn_80223870(u8* o) {
    lsClear((LS*)(o + 0x74));
    *(s16*)(o + 0x56) = 0;
}
struct LSO { u8 pad[0x74]; LS l; };
void* fn_802250A0(u8* o, int del) {
    if (o != NULL) {
        LS* l = (LS*)((u32)o + 0x74);
        if (l != NULL) if (l != NULL) { if (l != NULL) {
            LSO* s = (LSO*)o;
            LN* e;
            LN* p = s->l.next;
            e = (LN*)&s->l.prev;
            if (p != e) {
                LN* last = e->prev;
                p->prev->next = last->next;
                last->next->prev = p->prev;
                while (p != e) {
                    LN* t = p;
                    p = p->next;
                    fn_80079210(t);
                    s->l.size--;
                }
            }
        } }
        fn_801E2E00(o, 0);
        if (del > 0) fn_80079210(o);
    }
    return o;
}
}
