#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void* fn_801E5640(void*, int, int);
void* fn_801E041C(const char*, const char*);
void* fn_800D5448(void*, void*, int);
void* fn_800D0864(const char*);
void fn_80083DC4(void*, int);
void fn_801E5734(void*, void*);
void fn_801E4F50(void*, void*, int);
void fn_801E40B0(void*, int);
#if TARGET_PC
FE10_PROTO void* fn_80081050(void*, p32arg);
FE10_PROTO void* fn_80081194(void*, p32arg);
#else
void* fn_80081050(void*, int);
void* fn_80081194(void*, int);
#endif
void fn_801E4094(void*);
void* fn_801E2204(void*, void*, void*);
extern char lbl_803CAB38[];
u8* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
FE10_PROTO void fn_801EA538(void*, p32arg);
#else
void fn_801E7938(void*, int);
void fn_801EA538(void*, int);
#endif
struct XY { s16 x, y; };
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
static inline void setI(W* w, s16 a, s16 b, s16 c, s16 d) { w->ix0 = a; w->iy0 = b; w->ix1 = c; w->iy1 = d; }
#define FREE_FN(name) \
void* name(void* p, int del) { \
    if (p != NULL && del > 0) { \
        fn_80079210(p); \
    } \
    return p; \
}
int fn_80119F24(void*, void*);
u8 fn_80226BF0(void* a, void* b) { return fn_80119F24(a, b); }
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
static inline void setHelp(void* s, const char* const& str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
extern char lbl_80371E1C[];
void fn_8022860C(void* s) {
    u8* m = (u8*)fn_801E041C(0, 0);
    *(s16*)(m + 8) = 0x180;
    *(s16*)(m + 0xa) = 0x1b;
    m[0x24] = 1;
    fn_800D5448(m, s, 0);
    { Wi* t = (Wi*)fn_801E5640(s, 0x80, 0); t->a40 = lbl_80371E1C + 0x135; }
    setHelp(s, lbl_80371E1C + 0xf8);
}
struct Sc3 { u8 p[0x40]; u8 a40; };
#define HLP2(name, off) \
void name(Sc3* s) { \
    void* a = fn_801E5640(s, 0x81, 0); \
    void* b = fn_801E5640(s, 0x84, 0); \
    switch (s->a40) { \
    case 5: \
        if (a != NULL) fn_801E7938(a, *(int*)(fn_80060728(lbl_803CAB38) + off)); \
        if (b != NULL) fn_801EA538(b, *(int*)(fn_80060728(lbl_803CAB38) + off)); \
    } \
    fn_80083DC4(s, s->a40); \
}
HLP2(fn_80228BB8, 0x24)
HLP2(fn_80228C78, 0x28)
extern void* lbl_8038FF24[];
struct P60 { u8 p[0x40]; u8 a40; int b, c, d, e, f, g, h; };
P60* fn_80228D38(int x) {
    P60* o;
    if (x != 0) {
        o = (P60*)fn_80081194(lbl_8038FF24, x);
    } else {
        o = (P60*)fn_80081050(lbl_8038FF24, x);
    }
    if (o != NULL) {
        fn_801E4094(o);
        o->a40 = 0; o->b = 0; o->c = 0; o->d = 0; o->e = 0; o->f = 0; o->g = 0; o->h = 0;
    }
    return o;
}
extern char lbl_80390210[];
char* fn_80228F74(void) { return lbl_80390210; }
extern char lbl_803901FC[];
void* fn_80228F80(void) { return fn_800D0864(lbl_803901FC); }
extern char lbl_803901A4[];
char* fn_80229190(void) { return lbl_803901A4; }
extern char lbl_80390198[];
void* fn_8022919C(void) { return fn_800D0864(lbl_80390198); }
extern char lbl_80371F70[];
char* fn_8022A7C0(void) { return lbl_80371F70; }
void fn_8022B5A0(VO0N* o) { o->v24(); }
int fn_8022B5B0(void) { return 0x24; }
int fn_8022B5B8(void) { return 0x24; }
int fn_8022B5C0(u8* o) { return *(s16*)(o + 0x4a); }
int fn_8022B5C8(u8* o) { return *(s16*)(o + 0x48); }
int fn_8022B5D0(u8* o) { return *(s16*)(o + 0x44); }
int fn_8022B5D8(u8* o) { return *(s16*)(o + 0x46); }
FREE_FN(fn_8022B5E0)
void fn_8022C244(W* w) {
    setI(w, 10, 3, wW(w) - 10, wH(w) - 3);
    w->tx = 0x24;
    w->ty = 0;
}
FREE_FN(fn_8022C298)
void fn_8021696C(void*, int);
extern void* lbl_80390540[];
class RObj2 { public: virtual void destroy(int); int rc; };
struct S80 { void* vt; u8 p[0x78]; RObj2* a7c; };
/* fn_8022C2D8: near miss, see wip/fn_80226BF0.cpp */
S80* fn_8022C2D8(S80* o, int del);

extern void* lbl_80390498[];
class LS { public:
 virtual int v08(); virtual int v0C(); virtual void* v10(int, int); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(void*); virtual int v28(void*); virtual int v2C(); virtual int v30(); virtual s16 v34();
};
void* fn_8022C99C(LS* o) { return lbl_80390498[o->v34()]; }
void fn_801DA800(int, int, int, int, int, u32);
void fn_8022CAA4(LS* o) {
    W* w = (W*)o;
    o->v14();
    {
        s16 h = w->y1 - w->y0;
        s16 c = o->v34();
        fn_801DA800(0, 0, h, c, 1, *(u32*)((u8*)o + 0x38));
    }
}
void fn_8022D364(LS* o, void* a) {
    LS* c = (LS*)o->v10(0x81, 0);
    switch (*(int*)((u8*)o + 0x70)) {
    case 0:
        o->v24(a);
        break;
    case 1:
        if (c != NULL) c->v28(a);
        break;
    }
}
void fn_8022D998(void* s) {
    u8* w = (u8*)fn_801E5640(s, 0, 0);
    *(int*)(w + 0x70) = 1;
    fn_801E5734(s, w);
}
void fn_8022DD70(void* s) { fn_801E4F50(s, fn_801E5640(s, 0, 0), 1); }
void fn_8022DDB4(u8* o) {
    if (o != NULL) {
        if ((u8*)((u32)o + 0x44) != NULL && (u32)*(int*)(o + 0x44) >> 31) {
            fn_80079210(*(void**)(o + 0x4c));
        }
        fn_801E40B0(o, 0);
    }
}
int fn_8022DFD8(void) { return 4; }
extern char lbl_803902B0[];
struct Tb { const char* p[1]; };
static inline const char** tblOf(int k) { const char** t = NULL; switch (k) { case 0: t = (const char**)lbl_803902B0; } return t; }
int fn_8022B6A0(int k) {
    int n = 0;
    const char** t;
    t = tblOf(k);
    while (**t != '\n') { t++; n++; }
    return n;
}
/* fn_8022B620: near miss, see wip/fn_80226BF0.cpp */
int fn_8022B620(int k);

extern char lbl_80371F98[];
/* fn_8022B6DC: near miss, see wip/fn_80226BF0.cpp */
const char* fn_8022B6DC(int k, int x, int y);

const char* fn_8022A87C(u8* o) { return fn_8022B6DC(*(int*)(o + 0x40), *(s16*)(o + 0x4c), *(s16*)(o + 0x4e)); }
void fn_8022A890(VO0N* o) { o->v14(); }

void fn_8014C2AC(void*);
void fn_801E495C(void*, void*, void*, int);
void fn_80083B78(void*);
void fn_80253EE4(const char*, f32);
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CA870[0x130];
void fn_800D3C30(void*, int);
void* fn_801E7A28(void*);
struct Sm { u8 p[0x88]; u8* a88; };
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define ASKDLG(name) \
void name(Sm* s) { \
    u8* m = (u8*)fn_801E041C(0, 0); \
    *(s16*)(m + 8) = 0x180; \
    *(s16*)(m + 0xa) = 0x1b; \
    m[0x24] = 1; \
    fn_800D5448(m, s, 0); \
    setHelpV(s, *(const char**)(s->a88 + 0xac)); \
}
ASKDLG(fn_8022E514)
ASKDLG(fn_8022F57C)
ASKDLG(fn_80230394)
ASKDLG(fn_80230E60)
ASKDLG(fn_802318EC)
ASKDLG(fn_80233824)
ASKDLG(fn_80233A78)
void fn_8022E590(Sm* s) {
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        break;
    case 0x80:
        fn_8014C2AC(*(void**)(s->a88 + 0x84));
        setHelpV(s, *(const char**)(s->a88 + 0xa8));
        fn_80083DC4(s, 0x32);
        break;
    }
}
void fn_8022F570(Sm* s) { fn_8014C2AC(*(void**)(s->a88 + 0x14)); }
void fn_802318E0(Sm* s) { fn_8014C2AC(*(void**)(s->a88 + 0x34)); }
void fn_80234590(Sm* s) {
    fn_8014C2AC(*(void**)(s->a88 + 0x84));
    setHelpV(s, *(const char**)(s->a88 + 0xa8));
}
void fn_802345E8(Sm* s) {
    fn_8014C2AC(*(void**)(s->a88 + 8));
    setHelpV(s, *(const char**)(s->a88 + 0xa8));
}
struct WY { u8 p[0xa]; s16 x, y; };
static inline void mvx(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
void fn_8022EF08(void* s) {
    WY* w = (WY*)fn_801E5640(s, 0, 0);
    mvx(s, w, 0x134, w->y, 0);
}
void fn_8022F624(void* s) {
    WY* w = (WY*)fn_801E5640(s, 1, 0);
    mvx(s, w, 0x134, w->y, 0);
}
void fn_8022F5F8(void* s) {
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        break;
    case 0x80:
        fn_80083DC4(s, 9);
        break;
    }
}
extern char lbl_80372600[];
#define OKCLOSE(name) \
void name(void* s) { \
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) { \
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f); \
        fn_80083B78(s); \
    } \
}
OKCLOSE(fn_80230524)
OKCLOSE(fn_80232508)
OKCLOSE(fn_80234640)
struct S3C { u8 p[0x38]; u8* a38; u8* a3c; };
void fn_80232274(S3C* o) {
    if (o->a38[0x74] == 0 && o->a3c[0x48] == 0) fn_80083B78(o);
}
void fn_8023229C(S3C* o) {
    if (o->a38[0x74] == 0 && o->a3c[0x48] == 0) fn_80083B78(o);
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) fn_80083B78(o);
}
void fn_8023269C(u8* s) {
    fn_800D3C30(*(void**)(s + 0x8c), 0xc);
    fn_801E4F50(s, fn_801E5640(s, 5, 0), 0);
}
void fn_80232858(void) {}
void fn_8023285C(void* s) { fn_80083DC4(s, 0x21); }
void fn_80234454(u8* s) { fn_80083DC4(s, s[0x81]); }
#if TARGET_PC
FE10_PROTO extern void* lbl_804CBF28; FE10_PROTO extern void* lbl_804CBF38;
#else
extern int lbl_804CBF28; extern int lbl_804CBF38;
#endif
int
#if TARGET_PC
*
#endif
fn_802356AC(void) {
#if TARGET_PC
return (int*)lbl_804CBF28;
#else
return lbl_804CBF28;
#endif
}
int
#if TARGET_PC
*
#endif
fn_802356B4(void) {
#if TARGET_PC
return (int*)lbl_804CBF38;
#else
return lbl_804CBF38;
#endif
}
void fn_8031D284(void*, void*, int);
extern char lbl_804203A8[]; extern char lbl_80420660[];
void fn_802359A8(void* a) { fn_8031D284(lbl_804203A8, a, 0); }
void fn_80236A48(void* a) { fn_8031D284(lbl_80420660, a, 1); }
extern int lbl_804CBF48; extern char lbl_8041F090[];
void fn_803202B0(void*); void fn_8031FF98(void*);
void fn_8023578C(void) { if (lbl_804CBF48 != 0) fn_803202B0(lbl_8041F090); }
void fn_802357A8(void) {
    if (lbl_804CBF48 != 0) {
        fn_8031FF98(lbl_8041F090);
        lbl_804CBF48 = 0;
    }
}
int fn_8031D34C(void*, void*, int);
extern char lbl_804203C8[];
u32 fn_802359BC(int a) {
    u32 r;
    if (fn_8031D34C(lbl_804203C8, &r, a) == 1) return r;
    return 0;
}
extern char lbl_80420420[0x100];
u8 fn_802373AC(void) { return lbl_80420420[0xa4]; }
void memcpy(void*, const void*, u32);
bool fn_8023731C(void* d) {
    if (*(int*)(lbl_80420420 + 0xa0) != 0) {
        memcpy(d, lbl_80420420 + 0x80, 0xc);
        return 1;
    }
    return 0;
}
bool fn_80237364(void* d) {
    if (*(int*)(lbl_80420420 + 0xa0) != 0) {
        memcpy(d, lbl_80420420 + 0x8c, 0x10);
        return 1;
    }
    return 0;
}
class V34 { public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*);
};
void fn_8023445C(void* s) {
    void* a = fn_801E5640(s, 6, 0);
    V34* b = (V34*)fn_801E5640(s, 7, 0);
    fn_801E7938(a, *(int*)(fn_80060728(lbl_803CAB38) + 0x24));
    b->v34(fn_801E7A28(a));
}
}
