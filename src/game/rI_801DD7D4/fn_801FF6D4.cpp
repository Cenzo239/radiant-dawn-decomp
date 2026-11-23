#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {
extern char lbl_8036F03C[];
extern char lbl_8036EFBC[];
extern VO0N* lbl_804CB5B8;
void fn_80253EE4(const char*, f32);
void fn_801E1CC0(void*, int);

class LW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
};
#define F16(p, off) (*(s16*)((u8*)(p) + (off)))
typedef void (RObj::*MF)(int);
typedef struct FnT { MF f; int arg; } FnT;
struct RL2 { int size; LNode* prev; LNode* next; };
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
extern MF lbl_8038DDB0;
extern MF lbl_8038D070;
extern MF lbl_8038D094;
extern MF lbl_8038D0F0;
extern MF lbl_8038DDA4;
extern MF lbl_8038D064;
extern MF lbl_8038D088;
extern MF lbl_8038D0E4;
class MW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C();
    virtual int v50(); virtual int v54(); virtual int v58(int, int, int, int, int);
    u8 pad[0x3c];
    RL2 l;
};
typedef struct KB { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 pad2f[5]; RList l; } KB;
static inline BOOL kbTest(KB* a) { return a->x2d != 0 || a->x2e != 0; }
int fn_8028DB44(int);
int fn_800CB0FC(int, f32);
void fn_800712E8(int, int, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
#define DRAWL(fn, TBL, SZ, CU, px0) \
typedef struct P##fn { u8 pad[0x12]; s16 x12, x14, x16; u8 pad18[6]; s16 x1e, x20; u8 pad22[px0 - 0x22]; s16 p0, px, py; } P##fn; \
void fn(MW* o, KB* a) { \
    P##fn* q = (P##fn*)o; \
    FnT g; \
    u8* c; \
    s16 x; \
    s16 pxv; \
    int sel; \
    s16 n; \
    s16 y; \
    int tt; \
    s16 y2; \
    int i; \
    g.f = TBL; \
    g.arg = (int)a; \
    forEach(o->l.next, (LNode*)&o->l.prev, g); \
    o->v18(a); \
    i = o->v34(); \
    c = (u8*)o + i * 2; \
    n = *(u32*)((u8*)o + i * 12 + SZ); \
    if (n == 0) { \
        F16(c, 0x58) = 0; \
        F16(c, CU) = 0; \
    } \
    { int r = F16(c, CU) - F16(c, 0x58); r = (s16)r * 0x1c; y = r + q->x20; } \
    pxv = q->px; \
    x = q->x1e; \
    if ((pxv == -0x8000 && q->py == -0x8000) || (fn_8028DB44(pxv - x) <= 1 && fn_8028DB44(q->py - y) <= 1)) { \
        q->px = x; \
        q->py = y; \
    } else { \
        q->px = (pxv + x + 1) >> 1; \
        q->py = (y + q->py + 1) >> 1; \
    } \
    if (*((u8*)o + 0x51) != 0) { \
        sel = 0; \
        if (!kbTest(a)) { \
            if ((a->l.size != 0 ? a->l.prev->val : NULL) == (RObj*)o) { \
                sel = 1; \
            } \
        } \
        fn_8007E154(); \
        fn_8007E720(-*(f32*)((u8*)o + 0x54)); \
        fn_8007E164(); \
        fn_800712E8(q->px, q->py + ((0x1c - fn_800CB0FC(-1, 1.0f)) >> 1), sel); \
        { \
            f32 z = *(f32*)((u8*)o + 0x54) - 0.5f; \
            fn_8007E154(); \
            fn_8007E720(z); \
            fn_8007E164(); \
        } \
        o->v58(0, y, (s16)(q->x16 - q->x12), 0x1c, sel); \
    } \
    if (n != 0 && *((u8*)o + 0x52) != 0) { \
        o->v18(a); \
        fn_8007E154(); \
        fn_8007E720(1.0f + -*(f32*)((u8*)o + 0x54)); \
        fn_8007E164(); \
        { \
            { int r = q->p0 - F16(c, 0x58); r = (s16)r * 0x1c; y2 = r + q->x20; } \
            tt = (0x1c - fn_800CB0FC(-1, 1.0f)) >> 1; \
            fn_8007E154(); \
            fn_8007E7E8(0x40); \
            fn_8007E164(); \
            fn_800712E8(x, y2 + tt, 0); \
        } \
    } \
    fn_8007E154(); \
    fn_8007E7E8(0x80); \
    fn_8007E164(); \
}
DRAWL(fn_801FF6D4, lbl_8038DDA4, 0x98, 0x70, 0x88)
DRAWL(fn_801ED8FC, lbl_8038D064, 0x88, 0x68, 0x78)
DRAWL(fn_801EE904, lbl_8038D088, 0x74, 0x5e, 0x64)
DRAWL(fn_801EF90C, lbl_8038D0E4, 0x80, 0x64, 0x70)
}
