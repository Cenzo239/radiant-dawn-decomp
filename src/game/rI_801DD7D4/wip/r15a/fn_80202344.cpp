#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_8028BFD8(void*, void*, void*, int, int);
void fn_80204454(void* p);
void fn_801ECD88(void* p, void* arg);
void* memset(void*, int, u32);
extern u8 lbl_8038E548[], lbl_8038CED8[], lbl_8038E518[], lbl_8038E4E8[];
extern char lbl_8036FBC0[];
extern u8 lbl_803CAB38[];
int fn_80060754(void*);
void* fn_801059B0(void);
void fn_8014BED4(void*, void*);
void* fn_800D4188(const char*, void*);
void fn_800D3BCC(void*, int);
struct Z8 { u8 v; };
void fn_802044F4(void*, Z8*);
}
struct El { void f(); u8 p[0xc]; };
typedef void (El::*MF)();
struct FnE { MF f; };
extern "C" MF lbl_8038E4A4;
static inline void forEach(El* b, El* e, FnE f) {
    while (b != e) {
        (b->*f.f)();
        b++;
    }
}
struct W2 { u32 a, b; };
struct W3 { W2 ab; u32 c; };
extern "C" W3 lbl_803741A8;
struct T3 { int a, b, c; };
class VA { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(T3); };
class VL { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(void*, void*); };
struct BB { WF w; int a40; LN l44; int x4c; u8 x50, x51, x52; f32 x54; u8 x58[0x10]; u8 x68[0x10]; u8 p78[2]; s16 x7a, x7c, x7e; f32 x80; s16 x84, x86; El arr[8]; u8 pe8[8]; int xf0; u8 pf4[4]; WF* xf8; };
struct Nw { WF w; int a40; W3 a44; };
struct Unit { u8 p[0xe8]; Unit* next; u8 p2[0x1bc - 0xec]; struct Item { int x0; u8 p4[0x24]; } it[7]; };
struct Ctx { void* x0; u8 p4[0x2c]; int x30; };
struct Sc { u8 p[0x40]; BB* x40; u8 p44[4]; Ctx* x48; void* x4c; };
static inline void setXr(WF* w, s16 x) { w->x1 = x + (s16)(w->x1 - w->x0); w->x0 = x; }
static inline void setYr(WF* w, s16 y) { w->y1 = y + (s16)(w->y1 - w->y0); w->y0 = y; }
static inline int hgt(WF* w) { return (s16)(w->y1 - w->y0); }
static inline BB* mkB() {
    BB* b = (BB*)fn_80079150(0xfc);
    if (b) {
        gInit((G40*)b, 0xe0, 0x63, 0x238, 0x125, 0x158, 0xc2, 0x1f4, 0x10);
        b->w.vt = lbl_8038E548;
        b->x4c = 0;
        b->x50 = 0;
        b->x51 = 1;
        b->x52 = 0;
        b->x54 = 0.5f;
        b->x7a = -0x8000;
        b->x7c = -0x8000;
        b->x7e = 0;
        b->x80 = 0.0f;
        b->x84 = 0;
        b->x86 = 0;
        fn_8028BFD8(b->arr, fn_80204454, fn_801ECD88, 0xc, 8);
        b->xf0 = 0;
        memset(b->x58, 0, 0x10);
        memset(b->x68, 0, 0x10);
        {
            FnE g;
            g.f = lbl_8038E4A4;
            forEach(&b->arr[0], &b->arr[8], g);
        }
        b->w.vt = lbl_8038CED8;
        ((Lst*)b)->v2C();
        {
            Nw* n = (Nw*)fn_80079150(0x50);
            if (n) {
                s16 a = b->w.a26;
                wfInit(&n->w, 0, 0, 0x154, 0x20, 0x154, 0x20, a, 0x10);
                n->w.vt = lbl_8038E518;
                n->a40 = 0;
                n->a44 = lbl_803741A8;
                n->w.vt = lbl_8038E4E8;
            }
            b->xf8 = &n->w;
        }
        {
            T3 t = {0, 0x60, 0};
            WF* w = b->xf8;
            setXr(w, -b->w.ix0 );
            setYr(w, 4 - hgt(w));
            b->xf8->x1 = b->xf8->x0 + (s16)(b->w.x1 - b->w.x0);
            b->xf8->flags |= 0x10;
            ((VA*)b->xf8)->v2C(t);
            fn_801E2F40(b, b->xf8);
            b->w.tx = 0x12;
            b->w.ty = 8;
            b->x7e = 6;
        }
    }
    return b;
}
extern "C" void fn_80202344(Sc* o) {
    BB* b = mkB();
    o->x40 = b;
    if (b) b->w.rc++;
    o->x40->w.id = 0;
    o->x40->w.a28 = 8;
    {
        VL* l = (VL*)o->x40;
        for (Unit* u = (Unit*)((void**)lbl_804CB814)[0]; u; u = u->next) {
            Unit::Item* it = u->it;
            for (int i = 0; i < 7; i++, it++) {
                if (it == 0 || it->x0 == 0) break;
                l->v4C(it, u);
            }
        }
    }
    {
        VL* l = (VL*)o->x40;
        for (Unit* u = (Unit*)((void**)lbl_804CB814)[0xf]; u; u = u->next) {
            Unit::Item* it = u->it;
            for (int i = 0; i < 7; i++, it++) {
                if (it == 0 || it->x0 == 0) break;
                l->v4C(it, u);
            }
        }
    }
    if (fn_80060754(lbl_803CAB38)) {
        int* c = (int*)fn_801059B0();
        VL* l = (VL*)o->x40;
        int k = 0;
        for (int i = 0; i < c[0]; i++) {
            Unit::Item* it = (Unit::Item*)((u8*)c[1] + k);
            if (it && it->x0) l->v4C(it, 0);
            k += 0x28;
        }
    }
    {
        BB* q = o->x40;
        int i;
        u8 zz;
        int ofs=0; zz = i = 0; while (1) { Z8 z; z.v = zz; fn_802044F4(&q->arr[i], &z); ofs += 0xc; if (++i == 8) break; }
    }
    o->x40->x51 = 0;
    ((Lst*)o->x40)->v38(0);
    fn_801E5448(o, o->x40);
    fn_8014BED4(o->x48->x0, o);
    o->x4c = fn_800D4188(lbl_8036FBC0 + 0xc, o);
    fn_800D3BCC(o->x4c, 0xc);
    {
    int s = o->x48->x30;
    void* w = fn_801E5640(o, -0x1000, 0);
    if (w) *(int*)((u8*)w + 0x64) = s;
    }
}
