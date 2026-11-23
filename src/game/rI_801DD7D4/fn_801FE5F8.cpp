#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

extern u32 lbl_803CA870[];
extern char lbl_8036F03C[];
void fn_8028C0D0(void*, void*, int, int);
void fn_801E2E00(void*, int);
void* fn_801FDAF8(RList*, int);
u32* fn_801E2204(void*, void*, void*);
#if TARGET_PC
FE10_PROTO void fn_80107C80(p32arg, int, int, int);
#else
void fn_80107C80(u32, int, int, int);
#endif
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_801D8ADC(int, int, int, int);
void fn_801D820C(int, int, int, int, int, int);
void fn_80253EE4(const char*, f32);
int fn_8028C148(void*);

typedef struct IT { u8 pad[0x12]; u8 x12; } IT;
typedef struct IE { IT* x0; } IE;
int fn_801FE5F8(void* o, IE* e) {
    u8 t = e->x0 ? e->x0->x12 : 0x13;
    switch (t) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: case 13: return 3;
    case 4: return 4;
    case 6: return 5;
    case 7: return 6;
    case 8: return 7;
    case 9: return 8;
    case 10: return 9;
    case 11: return 10;
    case 14: case 15: case 16: return 11;
    default: return 13;
    }
}

void* fn_801FE698(void* o, int del) {
    if (o != NULL) {
        if (o != NULL) {
            fn_8028C0D0((u8*)o + 0x98, (void*)fn_801FDAF8, 0xc, 0xc);
            fn_801E2E00(o, 0);
        }
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}

typedef struct L3 { u32 size; u32 a, b; } L3;
class LW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44();
    u8 pad4[0x1a];
    s16 x1e, x20;
    u8 pad22[0x8e - 0x22];
    s16 x8e;
    u8 pad90[8];
    L3 l[1];
};
typedef struct C2 { u8 pad[0x58]; s16 x58; u8 pad5a[0x70 - 0x5a]; s16 x70; } C2;

#define SETCUR(fn, sz, rows, cu) \
void fn(LW* o, s16 t) { \
    if ((u32)t > *(u32*)((u8*)o + o->v34() * 12 + sz) - 1) { \
        t = *(u32*)((u8*)o + o->v34() * 12 + sz) - 1; \
    } \
    if (t < 0) { \
        t = 0; \
    } \
    { \
        u8* c = (u8*)o + o->v34() * 2; \
        u32 n = *(u32*)((u8*)o + o->v34() * 12 + sz); \
        s16 rw = *(s16*)((u8*)o + rows); \
        if (n <= rw) { \
            *(s16*)(c + cu) = t; \
            *(s16*)(c + 0x58) = 0; \
        } else if (n - t < rw) { \
            *(s16*)(c + cu) = t; \
            *(s16*)(c + 0x58) = n - rw; \
        } else if (*(s16*)(c + 0x58) < t && t - *(s16*)(c + 0x58) < rw - 1) { \
            *(s16*)(c + cu) = t; \
        } else if (t == 0) { \
            *(s16*)(c + 0x58) = t; \
            *(s16*)(c + cu) = t; \
        } else { \
            *(s16*)(c + cu) = t; \
            *(s16*)(c + 0x58) = t - 1; \
        } \
    } \
}
SETCUR(fn_801FE76C, 0x98, 0x8e, 0x70)
SETCUR(fn_80205594, 0x88, 0x7e, 0x68)
SETCUR(fn_802121F8, 0x74, 0x6a, 0x5e)
SETCUR(fn_80212348, 0x80, 0x76, 0x64)

typedef struct LWA { u8 pad[0x1e]; s16 x1e, x20; u8 pad22[0x58 - 0x22]; s16 x58[12]; s16 x70[12]; } LWA;

void fn_801FEF10(LW* o, s16 x, s16 y, void* p3, u32* it, int a) {
    fn_80107C80(*it, a, x, y);
    fn_8007E154();
    fn_8007E720(1.8f);
    fn_8007E164();
    {
        int m = o->x1e;
        s16 w = o->v3C() - m * 2;
        fn_801D8ADC(x, (s16)(y + o->v40() - 10), w, 0x10);
    }
    fn_8007E154();
    fn_8007E720(-1.8f);
    fn_8007E164();
}

typedef struct KB { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 pad2f[5]; RList l; } KB;
class Bt {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18();
    u8 pad4[0x38];
    u32 x3c;
    int x40;
};



extern VO0N* lbl_804CB5B8;
extern char lbl_8036FBC0[];
extern char lbl_803711E8[];
class T;
typedef void (T::*PFn)(void*, int, int);
typedef struct Bp { u8 pad[0x3c]; T* x3c; int x40; PFn x44; } Bp;
#define SEL(fn, mx, snd) \
void fn(Bp* o, void* a) { \
    u32 k; \
    int cur; \
    int n; \
    if (inputBlocked()) { \
        return; \
    } \
    k = lbl_804CB5B8->v3C(); \
    lbl_804CB5B8->v48(); \
    cur = o->x40; \
    if (k & 0x100001) { \
        n = cur - 1; \
        if (cur == 0) { \
            n = mx; \
        } \
        if (cur != n) { \
            if (o->x3c != NULL && o->x44 != NULL) { \
                (o->x3c->*o->x44)(a, n, 1); \
            } \
            fn_80253EE4(snd, 0.0f); \
        } \
    } else if (k & 0x200002) { \
        n = cur + 1; \
        if (cur == mx) { \
            n = 0; \
        } \
        if (cur != n) { \
            if (o->x3c != NULL && o->x44 != NULL) { \
                (o->x3c->*o->x44)(a, n, 2); \
            } \
            fn_80253EE4(snd, 0.0f); \
        } \
    } \
}
SEL(fn_801FFE90, 0xb, lbl_8036F03C + 0x2cb)
SEL(fn_8020540C, 7, lbl_8036FBC0 + 0xa5)
SEL(fn_80211D2C, 2, lbl_803711E8 + 0x29)
SEL(fn_80212070, 5, lbl_803711E8 + 0x29)

typedef struct LN { struct LN* prev; struct LN* next; RObj* val; } LN;
typedef void (RObj::*MF)(int);
typedef struct FnT { MF f; int arg; } FnT;
static inline void forEach(LN* n, LN* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
}
extern MF lbl_8038DDB0;

}
