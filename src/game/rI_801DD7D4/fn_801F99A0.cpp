#include "game/rI_801DD7D4/types.h"
extern "C" {
extern u8 lbl_8041EB20[];
extern char lbl_8036F03C[];
struct Ps { s16 x, y; };
void fn_801E5954(void*);
int fn_801A2224(void*);
void fn_801A1CFC(void*);
#if TARGET_PC
FE10_PROTO void fn_801A1F64(void*, p32arg, f32, f32);
FE10_PROTO void fn_801A1BE0(void*, void*, p32arg, f32, f32);
#else
void fn_801A1F64(void*, int, f32, f32);
void fn_801A1BE0(void*, void*, int, f32, f32);
#endif
void* fn_801E5640(void*, int, int);
void fn_80253EE4(const char*, f32);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E495C(void*, void*, void*, int);
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
struct LN { LN* prev; LN* next; u8 val[4]; };
struct RG { int size; LN* prev; LN* next; };
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual Ps v48(); };
struct SS { u8 p[0x50]; u8 x50, x51; u8 p52[0x70 - 0x52]; s16 cur[12]; u8 p88[0x10]; RG l[12]; };
struct Hd { u8 p[0x40]; int x40; int x44; };
static inline LN* adv(LN* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
static inline int* curVal(W* b) {
    int i = b->v34();
    SS* s = (SS*)b;
    s16* c = &s->cur[i];
    RG* r = &s->l[i];
    if (r->size == 0) return 0;
    return (int*)adv(r->next, *c)->val;
}
static inline Ps getPr(W* w) { Ps r = w->v48(); return r; }
static inline void help(void* o, const char* const& s) {
    void* w = fn_801E5640(o, -0x1000, 0);
    if (w) *(const char**)((u8*)w + 0x64) = s;
}
struct Sc { u8 p[0x54]; W* x54; Hd* x58; };
static inline void setI3(Hd* h, int t) { h->x44 = t; if (h->x44 == 0) h->x40 = 0; }
extern "C" void fn_801F99A0(Sc* o) {
/*P*/
    W* b;
    Hd* h;
    int* a;
    u32 e;
/*E*/
    b = o->x54;
    h = o->x58;
    a = curVal(b);
    if (a) {
        help(o, lbl_8036F03C + 0x1d3);
    } else {
        help(o, lbl_8036F03C + 0x1eb);
    }
    fn_801E5954(o);
    if (a != curVal(b)) {
        a = curVal(b);
        if (fn_801A2224(lbl_8041EB20)) {
            if (a) {
                Ps q = getPr(b);
                fn_801A1F64(lbl_8041EB20, *a, q.x, q.y);
            } else {
                fn_801A1CFC(lbl_8041EB20);
            }
        }
    }
    if (a) { h->x40 = a[1]; setI3(h, a[0]); } else { h->x40 = 0; setI3(h, 0); }
    if (((SS*)b)->x50 == 0 && !inputBlocked()) {
        e = lbl_804CB5B8->v48();
        if ((e & 0x400) && a && !fn_801A2224(lbl_8041EB20)) {
            fn_80083B78(o);
        } else if ((e & 0x2000) && !fn_801A2224(lbl_8041EB20) && a) {
            Ps q = getPr(b);
            fn_801A1BE0(lbl_8041EB20, o, *a, q.x, q.y);
            *(u32*)lbl_8041EB20 |= 2;
        } else if ((e & 0x2800) && fn_801A2224(lbl_8041EB20)) {
            fn_801A1CFC(lbl_8041EB20);
        } else if ((e & 0x800) && !fn_801A2224(lbl_8041EB20)) {
            fn_80083DC4(o, 0x24);
            fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
        }
    }
}
