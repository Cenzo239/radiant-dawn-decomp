#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8036EFBC[];
extern u8 lbl_803E7290[];
void fn_801E2204(void*, void*, void*);
void fn_801E2104(void* p, void* arg);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
const char* fn_800D0864(const char*);
int fn_800CA3DC(const char*, int, f32);
void fn_800CB278(s16, s16, int, const char*, ...);
typedef struct LN { struct LN* prev; struct LN* next; int val; } LN;
class KB;
class LV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(KB*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C();
    virtual int v50(int*); virtual int v54(s16, s16, int, int*, int); virtual int v58(); virtual int v5C();
};
struct FB { u8 pad[0x44]; };
class FV : public FB { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); };
#define F16(p, off) (*(s16*)((u8*)(p) + (off)))
#define FP(p, off) (*(f32*)((u8*)(p) + (off)))
static inline LN* adv(LN* it, s16 n) {
    if (n >= 0) {
        for (; n > 0; n--) it = it->next;
    } else {
        for (; n < 0; n++) it = it->prev;
    }
    return it;
}
static inline int sgn(s16 v) { return v < 0 ? -1 : v > 0; }
typedef void (RObj::*MF)(KB*);
typedef struct FnT { MF f; KB* arg; } FnT;
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
extern MF lbl_8038D058;
extern MF lbl_8038D07C;
extern MF lbl_8038D0D8;
extern MF lbl_8038DD98;
extern char lbl_8036F03C[];
typedef struct Child { u8 pad[0x40]; s16 x40, x42, x44; } Child;
typedef struct Base { u8 pad[0x12]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x40 - 0x22]; int lsize; LNode* lprev; LNode* lnext; Child* x4c; } Base;
#define ATS(name, SZ, CU) \
static inline int* name(LV* w, int i) { \
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
static inline void setR(Child* k, s16 a, s16 b, s16 c) { k->x40 = a; k->x42 = b; k->x44 = c; }
static inline int cen(int top, int fh) { fh = (0x1c - fh) >> 1; return top + fh; }
static inline void ixs(void* o, int i, u8*& c, u8*& s) { u8* c1; u8* s1; c1 = (u8*)o + i * 2; s1 = (u8*)o + i * 12; c=c1; s=s1; }
static inline void mapP(void* o, void* p) { fn_801E2204(o, p, p); }
static inline int toI(f32 v) { return (int)v; }
typedef struct PX2 { u8 pad[0x80]; f32 x80; } PX2;
typedef struct R8 { s16 a, b, c, d; } R8;
#define LIST(fn, TBL, XE, XR, XF, XP, SZ, CU, MSG) \
typedef struct P##fn { u8 pad[XF]; f32 f; u8 p84[XE - XF - 4]; R8 r; } P##fn; \
ATS(at##fn, SZ, CU) \
void fn(LV* o, KB* a) { \
    Base* b = (Base*)o; \
    P##fn* q = (P##fn*)o; \
    /*P*/ \
    int i; \
    int t; \
    LN* it; \
    s16 cur; \
    s16 n; \
    s16 rows; \
    s16 sg; \
    s16 x; \
    int yy; \
    s16 y; \
    int top; \
    int rem; \
    LNode* en; \
    int st; \
    s16 last; \
    KB* aa; \
/*E*/ \
    aa = a; \
    o->v5C(); \
    o->v18(aa); \
    { \
        s16 h = b->x18 - b->x14; \
        s16 w = b->x16 - b->x12; \
        q->r.a = 0; \
        q->r.b = 0; \
        q->r.c = w; \
        q->r.d = h; \
    } \
    mapP(o, &q->r.a); \
    mapP(o, &q->r.c); \
    { \
        i = o->v34(); \
        rows = F16(o, XR); \
        cur = *(s16*)((u8*)o + i * 2 + 0x58); \
        n = *(int*)((u8*)o + i * 12 + SZ); \
    } \
    fn_8007E154(); \
    fn_8007E74C(fn_801E2104, &q->r); \
    fn_8007E720(-1.0f); \
    fn_8007E164(); \
    { \
        t = (int)*(volatile f32*)&q->f; \
        if (q->f < 0.0f) { \
            q->f += 7.0f; \
            if (q->f >= -1.1920929e-07f) q->f = 0.0f; \
        } else if (q->f > 0.0f) { \
            q->f -= 7.0f; \
            if (q->f <= 1.1920929e-07f) q->f = 0.0f; \
        } \
    } \
    sg = sgn(t); \
    if (sg > 0 && cur > 0) cur = cur - 1; \
    it = adv(*(LN**)((u8*)o + i * 12 + SZ + 8), cur); \
    { \
        x = F16(o, XP) + b->x1e; \
        top = b->x20; \
        y = F16(o, XP + 2) + cen(top, ((FV*)lbl_803E7290)->v50()); \
        st = (sg > 0) ? -1 : 0; \
        last = sg < 0 ? rows + 1 : rows; \
        rem = n - cur; \
        yy = y + st * 0x1c; \
        for (; (s16)st < last; st++, it = it->next, yy += 0x1c) { \
            if ((s16)st >= rem) break; \
            { \
                int e = o->v50(&it->val); \
                o->v54(x, (s16)(t + yy), -1, &it->val, e); \
            } \
        } \
        if (at##fn(o, o->v34()) == NULL) { \
            const char* m = fn_800D0864(MSG); \
            int d = (s16)(b->x16 - b->x12); \
            d = (d - fn_800CA3DC(m, -1, 1.0f)) >> 1; \
            fn_8007E154(); \
            fn_8007E174(0, 0x13); \
            fn_8007E164(); \
            fn_800CB278(d + F16(o, XP), y, 0, m); \
        } \
    } \
    fn_8007E154(); \
    fn_8007E7B4(); \
    fn_8007E164(); \
    { \
        Child* k = b->x4c; \
        FnT g; \
        setR(k, n * 0x1c, rows * 0x1c, *(s16*)((u8*)o + i * 2 + 0x58) * 0x1c - t); \
        g.f = TBL; \
        g.arg = aa; \
        en = (LNode*)&b->lprev; forEach(b->lnext, en, g); \
    } \
}
LIST(fn_801ED290, lbl_8038D058, 0xe8, 0x7e, 0x80, 0x84, 0x88, 0x68, lbl_8036EFBC)
LIST(fn_801EE298, lbl_8038D07C, 0x98, 0x6a, 0x6c, 0x70, 0x74, 0x5e, lbl_8036EFBC)
LIST(fn_801EF2A0, lbl_8038D0D8, 0xc8, 0x76, 0x78, 0x7c, 0x80, 0x64, lbl_8036EFBC)
LIST(fn_801FF064, lbl_8038DD98, 0x128, 0x8e, 0x90, 0x94, 0x98, 0x70, lbl_8036F03C + 0x2a2)
}
