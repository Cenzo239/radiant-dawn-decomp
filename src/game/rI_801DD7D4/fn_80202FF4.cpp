#include "game/rI_801DD7D4/types.h"
extern "C" {
extern u8 lbl_8041EB20[];
extern u8 lbl_8036FBC0[];
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
void fn_80253EE4(void*, f32);
#if TARGET_PC
FE10_PROTO u32* fn_801116B8(p32arg);
FE10_PROTO int fn_80111094(p32arg);
#else
u32* fn_801116B8(int);
int fn_80111094(int);
#endif
void fn_800D0AE4(int, int);
#if TARGET_PC
FE10_PROTO void fn_8014C2AC(p32arg);
#else
void fn_8014C2AC(int);
#endif
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E495C(void*, void*, void*, int);
}
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual int v3C(); virtual void v40(); virtual void v44(); virtual int v48(); };
extern "C" Pad* lbl_804CB5B8;
struct LN { LN* prev; LN* next; u8 val[4]; };
struct RG { int size; LN* prev; LN* next; };
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual Ps v48(); };
struct SS { u8 p[0x50]; u8 x50, x51; u8 p52[0x68 - 0x52]; s16 cur[12]; u8 p80[8]; RG l[12]; };
struct Hd { u8 p[0x40]; int x40; int x44; };
struct Ctx { u8 p[0x10]; int x10; int x14; u8 p18[0x34-0x18]; int x34; };
struct Sc { u8 p[0x40]; W* x40; u8 p44[4]; Ctx* x48; };
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
static inline void setX(void* o, void* w, s16 x, int f) { s16 yy = *(s16*)((u8*)w + 0xc); Ps t; t.x = x; t.y = yy; fn_801E495C(o, w, &t, f); }
static inline void setX2(void* o, void* w, s16 x, int f) { setX(o, w, x, f); }
static inline void setX3(void* o, void* w, s16 x, int f) { setX2(o, w, x, f); }
struct PC : Ps { PC(s16 a, s16 b) { x = a; y = b; } };
static inline Ps mkp(s16 a, s16 b) { Ps t; t.x = a; t.y = b; return t; }
static inline void mv(void* o, void* w, Ps t, int f) { fn_801E495C(o, w, &t, f); }
static inline void mvr(void* o, void* w, const Ps& t, int f) { fn_801E495C(o, w, (Ps*)&t, f); }
static inline void mv2(void* o, void* w, s16 x, s16 y, int f) { Ps t; t.x = x; t.y = y; fn_801E495C(o, w, &t, f); }
static inline Ps getPr(W* w) { Ps r = w->v48(); return r; }
static inline BOOL fA(int id) { return *fn_801116B8(id) & 0x20000; }
static inline BOOL fB(int id) { return (((u8*)id)[5] >> 4) & 1; }
static inline Ps getP(W* w) { return w->v48(); }
static inline BOOL isOk(int id) { return fA(id) || fB(id); }
static inline void chk(int id, BOOL& r) { r = fA(id) || fB(id); }
static inline void act(Sc* o, int id) {
    BOOL ok;
            fn_80253EE4(lbl_8036FBC0 + 0x24, 0.0f);
            chk(id, ok);
            if (ok) {
                fn_8014C2AC(o->x48->x14);
                {
                int s = o->x48->x34;
                void* w = fn_801E5640(o, -0x1000, 0);
                if (w) *(int*)((u8*)w + 0x64) = s;
                }
                fn_80083DC4(o, 10);
            } else {
                fn_800D0AE4(0, fn_80111094(id));
                fn_8014C2AC(o->x48->x10);
                fn_80083B78(o);
            }
}
extern "C" void fn_80202FF4(Sc* o) {
/*P*/
    W* b;
    int* a;
    Hd* h;
    u32 e;
/*E*/
    b = o->x40;
    a = curVal(b);
    ((SS*)b)->x51 = 1;
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
    h = (Hd*)fn_801E5640(o, 2, 0);
    h->x40 = a ? a[1] : 0;
    h->x44 = a ? a[0] : 0;
    if (((SS*)b)->x50 == 0 && !inputBlocked()) {
        e = lbl_804CB5B8->v48();
        if ((e & 0x400) && a && !fn_801A2224(lbl_8041EB20)) {
            act(o, a[0]);
        } else if ((e & 0x2000) && !fn_801A2224(lbl_8041EB20) && a) {
            Ps q = getPr(b);
            fn_801A1BE0(lbl_8041EB20, o, *a, q.x, q.y);
            *(u32*)lbl_8041EB20 |= 2;
        } else if ((e & 0x2800) && fn_801A2224(lbl_8041EB20)) {
            fn_801A1CFC(lbl_8041EB20);
        } else if ((e & 0x800) && !fn_801A2224(lbl_8041EB20)) {
            ((SS*)b)->x51 = 0;
            mv2(o, h, 0x144, *(s16*)((u8*)h + 0xc), 0);
            fn_80083DC4(o, 11);
            fn_80253EE4(lbl_8036FBC0 + 0x34, 0.0f);
        }
    }
}
