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
struct SS { u8 p[0x50]; u8 x50, x51, x52; u8 p53[0x70 - 0x53]; s16 cur[12]; s16 x88; u8 p8a[0xe]; RG l[12]; };
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
extern "C" {
#if TARGET_PC
FE10_PROTO u32* fn_801116B8(p32arg);
#else
u32* fn_801116B8(int);
#endif
void fn_801E6B64(const char*, void*, f32, f32);
extern void* lbl_803CA870[];
extern u8 lbl_804CA990[8];
int fn_80127520(void*);
void fn_80129CB8(void*, int);
void fn_80102C6C(void*, void*, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_801EA538(void*, p32arg);
#else
void fn_801EA538(void*, int);
#endif
}
struct Sc2 { u8 p[0x44]; Hd* x44; u8 p48[0xc]; W* x54; Hd* x58; };
static inline void setI3(Hd* h, int t) { h->x44 = t; if (h->x44 == 0) h->x40 = 0; }
static inline Ps getPr2(W* w) { Ps r = w->v48(); return r; }
static inline BOOL fA(int id) { return *fn_801116B8(id) & 0x1000000; }
static inline BOOL fB(int id) { return (((u8*)id)[5] >> 2) & 1; }
static inline BOOL isOk(int* a) { int id = a[0]; BOOL ok; ok = fA(id) || fB(id); return ok; }
static inline void flush(Sc2* o) {
    s8 v = fn_80127520(lbl_803CA870[0]);
    if (v < 0) fn_80129CB8(lbl_803CA870[0], -1);
    {
    void* p = lbl_803CA870[0];
    if (p) fn_80102C6C(p, lbl_804CA990, 4, 0, 0);
    }
    {
    Hd* g = o->x44;
    if (g && g->x40) fn_801EA538(g, g->x40);
    }
}
extern "C" void fn_801F5A44(Sc2* o) {
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
        help(o, lbl_8036F03C + 0xb0);
    } else {
        help(o, lbl_8036F03C + 0xca);
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
            if ((fn_801116B8(a[0])[1] & 4) || isOk(a)) {
                Ps q = getPr(b);
                fn_801E6B64(lbl_8036F03C + 0xe5, o, q.x, q.y);
            } else {
                if (a[1] == 0) {
                    ((SS*)b)->x52 = 1;
                    {
                    int i = b->v34();
                    ((SS*)b)->x88 = ((SS*)b)->cur[i];
                    }
                    ((SS*)b)->x51 = 0;
                    fn_80083DC4(o, 0x10);
                } else {
                    flush(o);
                    ((int*)lbl_803CA870)[1] = a[1];
                    fn_80083DC4(o, 0x11);
                }
                fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
            }
        } else if ((e & 0x2000) && !fn_801A2224(lbl_8041EB20) && a) {
            Ps q = getPr(b);
            fn_801A1BE0(lbl_8041EB20, o, *a, q.x, q.y);
            *(u32*)lbl_8041EB20 |= 2;
        } else if ((e & 0x1000) && !fn_801A2224(lbl_8041EB20)) {
            flush(o);
            fn_80083DC4(o, 10);
            fn_80253EE4(lbl_8036F03C + 0x94, 0.0f);
        } else if ((e & 0x2800) && fn_801A2224(lbl_8041EB20)) {
            fn_801A1CFC(lbl_8041EB20);
        } else if ((e & 0x800) && !fn_801A2224(lbl_8041EB20)) {
            flush(o);
            fn_80083DC4(o, 0x12);
            fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
        }
    }
}
