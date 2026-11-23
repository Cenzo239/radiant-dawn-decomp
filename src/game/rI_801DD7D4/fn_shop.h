// Shared declarations for the shop scene functions in 0x80205000..0x80211000 (round 8).
// Struct layouts and inline shapes were chosen for code generation.
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
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
    u8 pad40[0x44 - 0x40];
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
    u8 pad[0xc];
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
    u8 pad50[0x68-0x50];
    const char* x68;
    const char* x6c;
    u8 pad70[0x74-0x70];
    const char* x74;
    u8 pad78[0x7c-0x78];
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
    u8 pad60[4];
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
int fn_801E7A28(void*);

static inline void lv3(W* w, f32& a) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { a = a * fn_801E33B4(p); } }
static inline void lv2(W* w, f32& a, f32& b) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv3(p, b); a = a * b; } }
static inline void lv1(W* w, f32& a, f32& b, f32& c) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv2(p, b, c); a = a * b; } }
static inline void lv0(W* w, f32& a, f32& b, f32& c, f32& d) { W* p; a = w->x30; p = w->x3c; if (p != NULL) { lv1(p, b, c, d); a = a * b; } }
static inline f32 scx343(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * fn_801E3468(p); } return f; }
static inline f32 scx342(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx343(p); } return f; }
static inline f32 scx341(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx342(p); } return f; }
static inline f32 scx340(W* w) { f32 f = w->x34; W* p = w->x3c; if (p != NULL) { f = f * scx341(p); } return f; }
class VW { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int); };
#if TARGET_PC
FE10_PROTO void fn_802056E4(void* p, ptr32<const void>);
#else
void fn_802056E4(void* p, void* arg);
#endif
#define ensure(w, id, f) \
    w = fn_801E5640(o, id, 0); \
    if (w == NULL) { \
        w = f; \
        fn_801E5448(o, w); \
    }
static inline void setCB(W* b, void (*f)(void), int k) { b->x7c = (void*)f; b->x80 = k; }
static inline void setH(Sc* o, Msgs* m) { const char* s = m->x68; W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) p->x64 = s; }



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
int fn_80105158(void*);
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
void fn_80207C50(void*);
void fn_80206C1C(void*);
void fn_8020D208(void*);
void fn_8020C1D4(void*);
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
typedef struct LS { struct LS* prev; struct LS* next; void* val; } LS;
struct Slot { int size; LS* prev; LS* next; };
typedef struct Item { int* x0; u8 pad[0x22]; u8 x26; } Item;
struct E0 { };
struct B2 { E0 op; Item* v; B2(Item* x) : v(x) {} };
static inline LS* findIf(LS* f, LS* l, B2 p) { while (f != l && f->val != p.v) f = f->next; return f; }
static inline LS* adv(LS* it, s16 n) {
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
        LS* it = adv(*(LS**)(s + SZ + 8), n); \
        return &it->val; \
    } \
}
ATS(atA, 0x74, 0x5e)
ATS(atB, 0x80, 0x64)
static inline int avail2() { int* m = fn_801059B0(); return *m - fn_80105158(m); }
void* fn_80079150(u32);
extern u8 lbl_8038CB1C[], lbl_8038CAF0[], lbl_8038CD00[];
extern void** lbl_804CB814;
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
struct LN { void* prev; void* next; };
struct G40 { WF w; int a40; LN l44; };
static inline void lnInit(LN* l) { l->next = l; l->prev = l; }
static inline void gInit(G40* g, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&g->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    g->w.vt = lbl_8038CAF0;
    g->a40 = 0;
    lnInit(&g->l44);
}
class Lst { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(); virtual int v38(void*); };
struct L84 { WF w; int a40; LN l44; int a4c; u8 a50, a51; s16 a52; u8 p54[2]; s16 a56, a58, a5a, a5c, a5e; f32 a60; s16 a64; u8 p66[0xa]; int a70; LN l74; void* a7c; int a80; void* a84; };
static inline void l84Init(L84* o, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    gInit((G40*)o, x0, y0, x1, y1, ix1, iy1, a26, fl);
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
static inline void mvx(Sc* o, W* w, s16 xv) { s16 y = w->xc; Pt p; p.x = xv; p.y = y; fn_801E495C(o, w, &p, 0); }
#if TARGET_PC
FE10_PROTO void fn_801A1F64(void*, p32arg, f32, f32);
#else
void fn_801A1F64(void*, int, f32, f32);
#endif
