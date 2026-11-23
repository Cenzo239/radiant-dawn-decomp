#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
void fn_80079210(void*);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E5734(void*, void*);
void fn_8014C2AC(void*);
void fn_80253EE4(const char*, f32);
void fn_801E495C(void*, void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4F50(void*, void*, int);
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CAB38[0x988];
extern char lbl_80372600[];
struct XY { s16 x, y; };
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
struct WY { u8 p[0xa]; s16 x, y; };
struct Sm { u8 p[0x88]; u8* a88; };
static inline void mvx(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define SL12 virtual int s08(); virtual int s0C(); virtual int s10(); virtual int s14(); virtual int s18(); virtual int s1C(); virtual int s20(); virtual int s24(); virtual int s28(); virtual int s2C(); virtual int s30(); virtual int s34();
class V38 { public: SL12 virtual void v38(int); };
class V382 { public: SL12 virtual void v38(int, int); };
void fn_801E5448(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void* fn_80079150(int);
void* fn_801E2204(void*, void*, void*);
class V18 { public: virtual int s08(); virtual int s0C(); virtual int s10(); virtual int s14(); virtual void v18(int); };
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
void fn_801E2104(void* p, void* arg);
void* fn_801246A4(void*);
void* fn_800C6210(void*, int);
void fn_800C4DDC(int, int, int, void*);
void fn_800C429C(void*);
void* fn_8012E3A4(void*);
struct D4 { s16 a, b; };
struct Dw { u8 p[0x40]; void* a40; D4 a44, a48, a4c, a50; };
struct UM { u8 p[0x48]; u8 a48; };
void fn_802137B8(Dw* o, int a) {
    void* u;
    ((VO0N*)o)->v30();
    ((V18*)o)->v18(a);
    u = o->a40;
    if (u != NULL) {
        o->a44.a = 6;
        o->a44.b = 6;
        o->a48.a = 0x86;
        o->a48.b = 0x86;
        fn_801E2204(o, &o->a44, &o->a44);
        fn_801E2204(o, &o->a48, &o->a48);
        fn_8007E154();
        fn_8007E74C((void*)fn_801E2104, &o->a44);
        fn_8007E164();
        {
            u32* m = (u32*)fn_800C6210(fn_801246A4(u), 0x200);
            m[0x48 / 4] = (m[0x48 / 4] & ~1) | 1;
            fn_800C4DDC(0x46, 0x86, 0xff, m);
            fn_800C429C(m);
        }
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
        {
            void* v = fn_8012E3A4(u);
            if (v != NULL) {
                o->a4c.a = 0x96;
                o->a4c.b = 6;
                o->a50.a = 0x116;
                o->a50.b = 0x86;
                fn_801E2204(o, &o->a4c, &o->a4c);
                fn_801E2204(o, &o->a50, &o->a50);
                fn_8007E154();
                fn_8007E74C((void*)fn_801E2104, &o->a4c);
                fn_8007E164();
                {
                    u32* m = (u32*)fn_800C6210(fn_801246A4(v), 0x200);
                    m[0x48 / 4] = m[0x48 / 4] & ~1;
                    fn_800C4DDC(0xd6, 0x86, 0xff, m);
                    fn_800C429C(m);
                }
                fn_8007E154();
                fn_8007E7B4();
                fn_8007E164();
            }
        }
    }
}
struct Node { u8 pad[0x2c]; f32 x2c, x30, x34; u8 pad38[4]; Node* parent; };
f32 fn_801E33B4(Node*);
#define chainY(a, k) { \
    f32 v3; f32 v2; f32 v1; f32 v0; Node* p; Node* q; Node* r; Node* o; \
    v0 = a->x30; p = a->parent; \
    if (p) { v1 = p->x30; q = p->parent; if (q) { v2 = q->x30; r = q->parent; if (r) { v3 = r->x30; o = r->parent; if (o) { v3 *= fn_801E33B4(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    fn_8007E7DC(k * v0); \
}
#define chainZ(a, k) { \
    f32 v0; f32 v1; f32 v2; f32 v3; Node* p; Node* q; Node* r; Node* o; \
    v0 = a->x30; p = a->parent; \
    if (p) { v1 = p->x30; q = p->parent; if (q) { v2 = q->x30; r = q->parent; if (r) { v3 = r->x30; o = r->parent; if (o) { v3 *= fn_801E33B4(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    fn_8007E7DC((u8)(int)(k * v0)); \
}
void fn_8007E7DC(u8);
#if TARGET_PC
FE10_PROTO void fn_801080CC(p32arg, int, int, int, p32arg);
#else
void fn_801080CC(int, int, int, int, int);
#endif
void fn_80222C68(Node* w, int a, int b, int, u32 c, int d, int e) {
    fn_8007E154();
    chainY(w, (f32)c);
    fn_8007E164();
    fn_801080CC(d, e, a, b, 0);
    fn_8007E154();
    chainZ(w, 255.99f);
    fn_8007E164();
}
struct WF { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26; s16 a28; u8 p2a[2]; f32 sx, sy, sz; int flags; int a3c; };
extern u8 lbl_8038CB1C[];
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
extern u8 lbl_8038FAA0[];
struct GW { WF w; int a40; void* a44; void* a48; u8 a4c; s16 a4e, a50, a52, a54, a56; u8 p58[8]; void* a60; int a64, a68; const char* a6c; };
void fn_80011CBC(void*, void*);
void fn_8021721C(void*);
void fn_80006EE0(void*);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
void fn_801E2E00(void*, int);
extern u8 lbl_8038C294[];
struct MB { void* vt; u8 p[0x24]; };
struct GX { GW g; u8 p70[8]; MB m[8]; };
#define MEMD(o, i) { MB* m = &o->m[i]; if (m != NULL) { if (m != NULL) { o->m[i].vt = lbl_8038C294; ((VO0N*)m)->v10(); } } }
GX* fn_8021D42C(GX* o, int del) {
    if (o != NULL) {
        MEMD(o, 7)
        MEMD(o, 6)
        MEMD(o, 5)
        MEMD(o, 4)
        MEMD(o, 3)
        MEMD(o, 2)
        MEMD(o, 1)
        MEMD(o, 0)
        if (o != NULL) {
            o->g.w.vt = lbl_8038FAA0;
            if (o->g.a60 != NULL) fn_80011CBC(fn_8021721C, o->g.a60);
            if (o->g.a64 != 0) fn_80011CBC(fn_80006EE0, (void*)o->g.a64);
            if (o->g.a68 != 0) fn_80011CBC(fn_8023F1A8, (void*)o->g.a68);
            fn_801E2E00(o, 0);
        }
        if (del > 0) fn_80079210(o);
    }
    return o;
}
void fn_80061808(void*, f32);
#if TARGET_PC
FE10_PROTO int fn_801204E8(p32arg);
FE10_PROTO void fn_8006CCAC(void*, p32arg, u8, void*, int);
#else
int fn_801204E8(int);
void fn_8006CCAC(void*, int, u8, void*, int);
#endif
extern u8 lbl_803C8E80[];
struct Tu { u8 p[0x40]; int a40; f32 a44; };
struct Sf { u8 p[0x44]; int a44; u8 p48[0x10]; Tu* a58; };
static inline const int& imin(const int& a, const int& b) { return a < b ? a : b; }
void fn_80220F28(Sf* s) {
    Tu* u = s->a58;
    f32 f = u->a44;
    int k = u->a40;
    fn_80061808(lbl_803CAB38, f);
    {
        int n = (u8)fn_801204E8(k);
        int m = imin(s->a44, n);
        s->a44 -= m;
        fn_8006CCAC(lbl_803C8E80, k, (u8)m, s, 0);
    }
    *(s16*)(lbl_803CAB38 + 0xb8) = 0;
}
struct GY { u8 p[0x4c]; MB m[5]; };
GY* fn_8021F4A8(GY* o, int del) {
    if (o != NULL) {
        MEMD(o, 4)
        MEMD(o, 3)
        MEMD(o, 2)
        MEMD(o, 1)
        MEMD(o, 0)
        if (del > 0) fn_80079210(o);
    }
    return o;
}
void fn_801E40B0(void*, int);
class RO { public: virtual void destroy(int); int rc; };
#define REL(o, f) { RO* p = o->f; if (p != NULL) { if (--p->rc == 0 && p != NULL) p->destroy(1); o->f = NULL; } }
struct Rs { u8 p[0x48]; RO* a48; RO* a4c; RO* a50; RO* a54; RO* a58; };
void fn_8021F8C8(Rs* o) {
    if (o != NULL) {
        REL(o, a54)
        REL(o, a48)
        REL(o, a4c)
        REL(o, a50)
        REL(o, a58)
        fn_801E40B0(o, 0);
    }
}
}
