#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

extern char lbl_803711E8[];
extern char lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern VO0N* lbl_804CB5B8;
typedef struct Pt { s16 x, y; } Pt;
typedef struct W {
    u8 pad[8];
    u8 x8[2];
    s16 xa, xc, xe, x10;
    u8 paxe[0x30 - 0x12];
    f32 x30, x34;
    u8 pad38[4];
    struct W* x3c;
    int x40b;
    struct { u8 pad[0x26]; u8 x26; }* x44p;
    s16 x48;
    u8 pad4a[2];
    u8 x4c;
    u8 x4d;
    u8 x4e;
    u8 pad4f;
    u8 x50, x51;
    u8 pad52[0x64-0x52];
    const char* x64;
    u8 x68;
    u8 pad69[0x7c-0x69];
    void* x7c;
    int x80;
} W;
typedef struct Msgs {
    u8 p0[4]; int x4; int x8;
    int xc;
    int x10, x14, x18, x1c;
    u8 pad20[0x24-0x20];
    int x24;
    int x28, x2c;
    int x30;
    int x34;
    int x38;
    u8 pad3c[4];
    int x40;
    int x44, x48;
    int x4c;
    int x50; int x54; int x58; int x5c; u8 pad60[0x64-0x60]; const char* x64s;
    const char* x68;
    const char* x6c;
    const char* x70;
    const char* x74;
    const char* x78;
    const char* x7c;
} Msgs;
class RO {
public:
    virtual void destroy(int);
    int rc;
};
typedef struct Sc {
    u8 pad[0x4c];
    W* x4c;
    W* x50;
    W* x54;
    RO* x58;
    u8 pad5c[2];
    u8 x5e;
    u8 pad5f;
    f32 x60;
    Msgs* x64;
    void* x68;
} Sc;

typedef struct K { u8 pad[8]; s16 x8, xa; u8 pad_c[0x24-0xc]; u8 x24; } K;
K* fn_801E041C(const char*, const char*);
void fn_800D5448(void*, void*, int);
W* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_801E5734(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
void fn_801E4D1C(void*, void*, int);
void fn_801E4F50(void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
f32 fn_801E33B4(W*);
f32 fn_801E3468(W*);
#if TARGET_PC
FE10_PROTO void fn_8014C2AC(p32arg);
#else
void fn_8014C2AC(int);
#endif
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_800D3C30(void*, int);
void fn_80253EE4(const char*, f32);
void* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_801E7A28(void*);
#else
int fn_801E7A28(void*);
#endif

static inline f32 scx303(W* w) { f32 f = w->x30; W* p = w->x3c; if (p != NULL) { f = f * fn_801E33B4(p); } return f; }
static inline f32 scx302(W* w) { f32 f = w->x30; W* p = w->x3c; if (p != NULL) { f = f * scx303(p); } return f; }
static inline f32 scx301(W* w) { f32 f = w->x30; W* p = w->x3c; if (p != NULL) { f = f * scx302(p); } return f; }
static inline f32 scx300(W* w) { f32 f = w->x30; W* p = w->x3c; if (p != NULL) { f = f * scx301(p); } return f; }
static inline void lv3(W* w, f32& a) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { a = a * fn_801E33B4(p); } }
static inline void lv2(W* w, f32& a, f32& b) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv3(p, b); a = a * b; } }
static inline void lv1(W* w, f32& a, f32& b, f32& c) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv2(p, b, c); a = a * b; } }
static inline void lv0(W* w, f32& a, f32& b, f32& c, f32& d) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv1(p, b, c, d); a = a * b; } }
static inline f32 scx343(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * fn_801E3468(p); } return f; }
static inline f32 scx342(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx343(p); } return f; }
static inline f32 scx341(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx342(p); } return f; }
static inline f32 scx340(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx341(p); } return f; }
class VW { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int); };
void fn_802056E4(void* p, void* arg);
#define ensure(w, id, f) \
    w = fn_801E5640(o, id, 0); \
    if (w == NULL) { \
        w = f; \
        fn_801E5448(o, w); \
    }
static inline void setCB(W* b, void (*f)(void*, void*), int k) { b->x7c = (void*)f; b->x80 = k; }
static inline void setH(Sc* o, Msgs* m) { const char* s = m->x68; W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) p->x64 = s; }
#define S6(fn) \
void fn(Sc* o) { \
    W* a; \
    W* b; \
    ensure(a, 7, (W*)o->x58); \
    { f32 f0, f1, f2, f3; lv0(a, f0, f1, f2, f3); if (1.0f != f0) { \
        fn_801E4D1C(o, a, 0); \
    } } \
    b = fn_801E5640(o, 3, 0); \
    b->x50 = 1; \
    if (b->xc != 0x1c) { \
        s16 x = b->xa; \
        Pt p; \
        p.x = x; \
        p.y = 0x1c; \
        fn_801E459C(o, b, &p, 1); \
    } \
    b->x51 = 0; \
    setCB(b, fn_802056E4, a->x48); \
    if (1.0f != scx340(b)) { \
        fn_801E518C(o, b, 0, 1.0f); \
    } \
    a = fn_801E5640(o, 4, 0); \
    if (a->xa != 0x20) { \
        s16 y = a->xc; \
        Pt p; \
        p.x = 0x20; \
        p.y = y; \
        fn_801E459C(o, a, &p, 0); \
    } \
    ((VW*)a)->v34(fn_801E7A28(b)); \
    a->x4c = 0; \
    a->x68 = 0; \
    a->x4e = 1; \
    { \
        W* c = fn_801E5640(o, 6, 0); \
        if (c != NULL && c->xa != 0x150) { \
            s16 y = c->xc; \
            Pt p; \
            p.x = 0x150; \
            p.y = y; \
            fn_801E459C(o, c, &p, 0); \
        } \
    } \
    { \
        W* c = fn_801E5640(o, 5, 0); \
        if (c->xa != 0x12a) { \
            s16 y = c->xc; \
            Pt p; \
            p.x = 0x12a; \
            p.y = y; \
            fn_801E459C(o, c, &p, 0); \
        } \
    } \
    fn_801E5734(o, b); \
    setH(o, o->x64); \
}
#define SHOW(fn) \
void fn(Sc* o) { \
    W* w; \
    ensure(w, 0, o->x4c); \
    if (w->xa != 0xe0) { \
        s16 y = w->xc; \
        Pt p; \
        p.x = 0xe0; \
        p.y = y; \
        fn_801E459C(o, w, &p, 0); \
    } \
    ensure(w, 1, o->x54); \
    if (w->xa != 0x14e) { \
        s16 y = w->xc; \
        Pt p; \
        p.x = 0x14e; \
        p.y = y; \
        fn_801E459C(o, w, &p, 0); \
    } \
    ensure(w, 2, o->x50); \
    { f32 f3, f2, f1, f0; lv0(w, f0, f1, f2, f3); if (1.0f != f0) { \
        fn_801E4D1C(o, w, 0); \
    } } \
}
SHOW(fn_80208844)
SHOW(fn_8020DDFC)
S6(fn_80209450)
S6(fn_8020EA08)

extern char lbl_8041EB20[];
int fn_801A2224(void*);
void fn_801A1CFC(void*);
#if TARGET_PC
FE10_PROTO void fn_801A1BE0(void*, void*, p32arg, f32, f32);
FE10_PROTO int fn_80111074(p32arg);
#else
void fn_801A1BE0(void*, void*, int, f32, f32);
int fn_80111074(int);
#endif
int fn_800626E0(void*);
int fn_80060754(void*);
int* fn_801059B0(void);
int fn_80105158(void* m);
void fn_800D0AE4(int, int);
void fn_800D3BCC(void*, int);
void fn_801E5954(void*);
#if TARGET_PC
FE10_PROTO void fn_801EA538(void*, p32arg);
FE10_PROTO void fn_801E6C44(p32arg, void*, p32arg);
FE10_PROTO void fn_801E6D50(p32arg, void*);
#else
void fn_801EA538(void*, int);
void fn_801E6C44(int, void*, int);
void fn_801E6D50(int, void*);
#endif
#define HELP(o, fld) {     const char* s = o->x64->fld;     W* p = fn_801E5640(o, -0x1000, 0);     if (p != NULL) {         p->x64 = s;     } }
#define SND(k) fn_80253EE4(lbl_803711E8 + k, 0.0f)
#define RELEASE(o) {     RO* r = o->x58;     if (r != NULL) {         if (--r->rc == 0) {             if (r != NULL) {                 r->destroy(1);             }         }         o->x58 = NULL;     } }
class VS { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual u32 v30(); virtual int v34(int); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(int); };
struct Ps { s16 x, y; };
#define MV(w, xv, yv) {     s16 y = yv;     Pt p;     p.x = xv;     p.y = y;     fn_801E495C(o, w, &p, 0); }

extern char lbl_8041EB20[];
static inline Pt mk(u32 r) { Pt p; p.x = r >> 16; p.y = r; return p; }
void fn_80207EEC_(void);
#define PRICE(o, it) ((int)(*(f32*)((u8*)o + 0x60) * (f32)fn_80111074(it)))
#define BUYK(fn) \
void fn(Sc* o) { \
    ((W*)o->x58)->x4c = 1; \
    fn_801E5954(o); \
    if (!inputBlocked()) { \
        int k = ((VS*)lbl_804CB5B8)->v48(); \
        if ((k & 0x400) && fn_801A2224(lbl_8041EB20) == 0) { \
            W* a = (W*)o->x58; \
            int it = (int)a->x44p; \
            s16 n = a->x48; \
            int pr = PRICE(o, it); \
            if (pr * n > fn_800626E0(lbl_803CAB38)) { \
                SND(0x74); \
                fn_8014C2AC(o->x64->x34); \
                HELP(o, x74); \
                o->x5e = 8; \
                fn_80083DC4(o, 0x13); \
            } else { \
                SND(0x82); \
                fn_801E4F50(o, o->x58, 0); \
                { \
                    s16 n2 = ((W*)o->x58)->x48; \
                    int pr2 = PRICE(o, it); \
                    fn_800D0AE4(0, pr2 * n2); \
                } \
                fn_8014C2AC(o->x64->x1c); \
                fn_80083B78(o); \
            } \
        } else if ((k & 0x2000) && fn_801A2224(lbl_8041EB20) == 0) { \
            Pt p = mk(((VS*)o->x58)->v30()); \
            fn_801A1BE0(lbl_8041EB20, o, (int)((W*)o->x58)->x44p, p.x, p.y); \
            *(u32*)lbl_8041EB20 |= 2; \
        } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20) != 0) { \
            fn_801A1CFC(lbl_8041EB20); \
        } else if ((k & 0x800) && fn_801A2224(lbl_8041EB20) == 0) { \
            fn_801E4F50(o, o->x58, 0); \
            RELEASE(o); \
            fn_801E5734(o, fn_801E5640(o, 0, 0)); \
            fn_8014C2AC(o->x64->xc); \
            HELP(o, x7c); \
            fn_80083DC4(o, 5); \
            SND(0x92); \
        } \
    } \
}
BUYK(fn_80207EEC)
BUYK(fn_8020D4A4)

extern char lbl_803CA870_[];
#if TARGET_PC
FE10_PROTO int fn_8012BDFC(p32arg);
#else
int fn_8012BDFC(int);
#endif
void fn_80079210(void*);
#if TARGET_PC
FE10_PROTO void fn_8012A440(p32arg, p32arg);
#else
void fn_8012A440(int, int);
#endif
void fn_800615DC(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80105260(void*, p32arg);
#else
void fn_80105260(void*, int);
#endif
void fn_802121F8(void*, int);
class VL { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); };
typedef struct LN { struct LN* prev; struct LN* next; void* val; } LN;
struct Slot { int size; LN* prev; LN* next; };
typedef struct Item { int* x0; u8 pad[0x22]; u8 x26; } Item;
struct E0 { };
struct B2 { E0 op; Item* v; B2(Item* x) : v(x) {} };
static inline LN* findIf(LN* f, LN* l, B2 p) { while (f != l && f->val != p.v) f = f->next; return f; }
static inline LN* adv(LN* it, s16 n) {
    if (n >= 0) {
        for (; n > 0; n--) it = it->next;
    } else {
        for (; n < 0; n++) it = it->prev;
    }
    return it;
}
#define ATS(name, SZ, CU) \
static inline void** name(VL* w, int i) { \
    u8* c; u8* s; \
    c = (u8*)w + i * 2; \
    s = (u8*)w + i * 12; \
    if (*(int*)(s + SZ) == 0) return NULL; \
    { \
        s16 n = *(s16*)(c + CU); \
        LN* it = adv(*(LN**)(s + SZ + 8), n); \
        return &it->val; \
    } \
}
ATS(atA, 0x74, 0x5e)
static inline int avail2() { int* m = fn_801059B0(); return *m - fn_80105158(m); }

static inline void setHf(Sc* o, const char* s) { W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) p->x64 = s; }
#define BACK2(fn) \
void fn(Sc* o) { \
    W* a; \
    W* b; \
    W* c; \
    ensure(a, 0, o->x4c); \
    if (a->xa != 0xe0) { \
        s16 y = a->xc; \
        Pt p; \
        p.x = 0xe0; \
        p.y = y; \
        fn_801E459C(o, a, &p, 0); \
    } \
    ensure(b, 1, o->x54); \
    if (b->xa != 0x14e) { \
        s16 y = b->xc; \
        Pt p; \
        p.x = 0x14e; \
        p.y = y; \
        fn_801E459C(o, b, &p, 0); \
    } \
    ensure(c, 2, o->x50); \
    { f32 f3, f2, f1, f0; lv0(c, f0, f1, f2, f3); if (1.0f != f0) { \
        fn_801E4D1C(o, c, 0); \
    } } \
    fn_801E5734(o, a); \
    setHf(o, o->x64->x7c); \
}
BACK2(fn_80206C1C)
BACK2(fn_8020C1D4)

typedef struct LN2 { struct LN2* prev; struct LN2* next; u8 v[4]; } LN2;
typedef struct SD { void* vt; int rc; u8 pad[0x40 - 8]; int size; LN2* prev; LN2* next; RO* x4c; RO* x50; RO* x54; RO* x58; } SD;
extern u32 lbl_804CB878;
void fn_80111C24(void*, int);
void fn_801E40B0(void*, int);
void fn_80079210(void*);
#define RELF(o, f) { \
    RO* r = o->f; \
    if (r != NULL) { \
        if (--r->rc == 0) { \
            if (r != NULL) { \
                r->destroy(1); \
            } \
        } \
        o->f = NULL; \
    } \
}
#define SDTOR(fn) \
void fn(SD* o) { \
    lbl_804CB878 &= ~0x10; \
    if (o != NULL) { \
        RELF(o, x4c); \
        RELF(o, x50); \
        RELF(o, x54); \
        RELF(o, x58); \
        { \
            int* l = &o->size; \
            if (l != NULL) { \
                if (l != NULL) { \
                    if (l != NULL) { \
                        LN2* e; \
                        LN2* n; \
                        n = o->next; \
                        e = (LN2*)&o->prev; \
                        if (n != e) { \
                            LN2* b = e->prev; \
                            n->prev->next = b->next; \
                            b->next->prev = n->prev; \
                            while (n != e) { \
                                LN2* d; \
                                fn_80111C24(n->v, -1); \
                                d = n; \
                                n = n->next; \
                                fn_80079210(d); \
                                o->size--; \
                            } \
                        } \
                    } \
                } \
            } \
        } \
        fn_801E40B0(o, 0); \
    } \
}
SDTOR(fn_8020B250)
SDTOR(fn_80210808)

typedef struct Un { u8 pad[0xec]; int xec; u8 p0[4]; struct { u8 pad[8]; u8 x8; }* xf4; u8 pad2[0x3f0 - 0xf8]; } Un;
extern Un* lbl_804CB810;
extern int lbl_804CAA08[1];
extern u8 lbl_804CAA14[3];
void* memset(void*, int, unsigned int);
int fn_80129A8C(Un*);
int fn_80105194(void*);
static inline Un* unitAt(int id) { return (u8)id != 0 ? &lbl_804CB810[(u8)id - 1] : NULL; }
typedef struct Un3F0 { u8 x[0x3f0]; } Un3F0;
static inline int canAny(void) {
    int found = 0;
    u8 kinds[3] = {0, 5, 0xff};
    u8 mask[0xb];
    memset(mask, (u8)lbl_804CAA08[0], 0xb);
    {
        u8* k = kinds;
        while (*k != 0xff) {
            mask[*k] = 1;
            k++;
        }
    }
    {
        int u;
        for (u = 1; u <= 0xfe; u++) {
            Un* n = unitAt(u);
            if (n->xec != 0 && mask[n->xf4->x8] != 0 && fn_80129A8C(n) >= 0) {
                found = 1;
                break;
            }
        }
    }
    if (found == 0 && fn_80060754(lbl_803CAB38) != 0) {
        if (fn_80105194(fn_801059B0()) >= 0) found = 1;
    }
    return found;
}
#define CHK(fn) \
void fn(Sc* o) { \
    if (canAny() != 0) { \
        fn_8014C2AC(o->x64->x4); \
        setHf(o, o->x64->x70); \
    } else { \
        fn_8014C2AC(o->x64->x54); \
        setHf(o, o->x64->x74); \
        fn_80083DC4(o, 0x17); \
    } \
}
CHK(fn_8020616C)
CHK(fn_8020B724)

#define MV(w, xv, yv) { \
    s16 y = yv; \
    Pt p; \
    p.x = xv; \
    p.y = y; \
    fn_801E495C(o, w, &p, 0); \
}
#define CANCEL(fn, back) \
void fn(Sc* o) { \
    W* a; W* b; W* c; W* d; \
    a = fn_801E5640(o, 3, 0); \
    fn_801E5640(o, 7, 0); \
    b = fn_801E5640(o, 4, 0); \
    c = fn_801E5640(o, 6, 0); \
    d = fn_801E5640(o, 5, 0); \
    { \
        s16 x = a->xa; \
        Pt p; \
        p.x = x; \
        p.y = -0x24; \
        fn_801E495C(o, a, &p, 0); \
    } \
    MV(b, -0x34, b->xc); \
    if (c != NULL) { \
        MV(c, 0x1a4, c->xc); \
    } \
    MV(d, 0x17e, d->xc); \
    RELEASE(o); \
    back(o); \
    if (canAny() != 0) { \
        fn_8014C2AC(o->x64->x8); \
        setHf(o, o->x64->x64s); \
        fn_80083DC4(o, 5); \
    } else { \
        fn_8014C2AC(o->x64->x58); \
        setHf(o, o->x64->x74); \
        fn_80083DC4(o, 0x17); \
    } \
}
#pragma use_lmw_stmw on
CANCEL(fn_8020A93C, fn_80206C1C)
CANCEL(fn_8020FEF4, fn_8020C1D4)
#pragma use_lmw_stmw off
#define NOMONEY(fn) \
void fn(Sc* o) { \
    W* a; W* b; W* c; \
    ensure(a, 0, o->x4c); \
    if (a->xa != 0xe0) { \
        s16 y = a->xc; \
        Pt p; \
        p.x = 0xe0; \
        p.y = y; \
        fn_801E459C(o, a, &p, 0); \
    } \
    ensure(a, 7, (W*)o->x58); \
    { f32 f0, f1, f2, f3; lv0(a, f0, f1, f2, f3); if (1.0f != f0) { \
        fn_801E4D1C(o, a, 0); \
    } } \
    a->x40b = 1; \
    ensure(b, 1, o->x54); \
    if (b->xa != 0x14e) { \
        s16 y = b->xc; \
        Pt p; \
        p.x = 0x14e; \
        p.y = y; \
        fn_801E459C(o, b, &p, 0); \
    } \
    ensure(c, 2, o->x50); \
    if (1.0f != scx300(c)) { \
        fn_801E4D1C(o, c, 0); \
    } \
    fn_801E5734(o, a); \
    setHf(o, o->x64->x64s); \
}
NOMONEY(fn_80207C50)
NOMONEY(fn_8020D208)

#define BLK(fn, mid) \
void fn(Sc* o) { \
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0)); \
    if (!inputBlocked() && (((VS*)lbl_804CB5B8)->v48() & 0xc00)) { \
        mid \
        fn_80083B78(o); \
    } \
}
BLK(fn_8020AE94, fn_801E5734(o, fn_801E5640(o, 3, 0)); fn_8014C2AC(o->x64->x50); SND(0xb5);)
BLK(fn_8020AF5C, fn_8014C2AC(o->x64->x5c); SND(0xb5); setHf(o, o->x64->x78);)
void fn_8020B0CC(Sc* o) {
    W* a = fn_801E5640(o, 3, 0);
    W* b = fn_801E5640(o, 4, 0);
    fn_801E7938(a, *(int*)((u8*)fn_80060728(lbl_803CAB38) + 0x28));
    ((VS*)b)->v34(fn_801E7A28(a));
    fn_80083DC4(o, o->x5e);
}
}
