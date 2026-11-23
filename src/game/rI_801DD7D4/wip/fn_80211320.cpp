/* wip near misses for fn_80211320.cpp (whole file kept so declarations stay together):
   fn_80211384: 5 of 7 words differ
   fn_802113E0: 5 of 7 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
void* fn_801059B0(void);
int fn_80105158(void* m);
void fn_800D0AE4(int, int);
void fn_801E1894(void*, void*);
void fn_801D74B4(int, int, int, int, int, int);
void fn_801D9428(int, int, int, int, int);

void fn_80211320(void* o, void* a) {
    int* p = (int*)fn_801059B0();
    fn_800D0AE4(0, *p - fn_80105158(p));
    fn_801E1894(o, a);
}

typedef struct Tri { int a, b, c; } Tri;

void fn_80211384(u8* o, Tri* t) {
    int a = t->a;
    int b = t->b;
    int c = t->c;
    Tri* d = (Tri*)(o + 0x44);
    d->a = a;
    d->b = b;
    d->c = c;
}

void fn_802113E0(u8* o, Tri* t) {
    int a = t->a;
    int b = t->b;
    int c = t->c;
    Tri* d = (Tri*)(o + 0x44);
    d->a = a;
    d->b = b;
    d->c = c;
}

#define FREE_FN(name) \
void* name(void* p, int del) { \
    if (p != NULL && del > 0) { \
        fn_80079210(p); \
    } \
    return p; \
}

FREE_FN(fn_802113A0)
FREE_FN(fn_802113FC)
FREE_FN(fn_8021143C)
FREE_FN(fn_8021147C)

void fn_80211D1C(VO0* o) { o->v18(); }
void fn_80211EA4(VO0* o) { o->v24(); }
void fn_80212060(VO0* o) { o->v18(); }
void fn_802121E8(VO0* o) { o->v24(); }

FREE_FN(fn_80212498)

typedef struct Grid {
    u8 pad[0xa];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    u8 pad22[0x40 - 0x22];
    u8* x40;
    u8 pad44[0x52 - 0x44];
    s16 x52, x54, x56;
} Grid;

class GridV {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34(int);
    virtual void v38(int);
};

void fn_80212558(Grid* o) {
    ((GridV*)o)->v14();
    fn_801D74B4(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), (*(u8**)(o->x40 + 0xf4))[8], 0x10);
}

void fn_802132B4(GridV* o, int a) {
    o->v34(a);
    o->v38(a);
}

void fn_80213390(Grid* o) {
    ((GridV*)o)->v14();
    fn_801D9428(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), 0x10);
}

}
