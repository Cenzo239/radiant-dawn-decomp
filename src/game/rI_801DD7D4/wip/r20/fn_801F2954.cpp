/* fn_801F2954, zero-idiom family, round 20 copy: complete self-contained draft, class `other`.
 * Source: wip/r19zero/fn_801F2954.cpp, improved this round: 922 of 922 instructions (was 914).
 * Fix (a real bug of the earlier draft): lbl_8038D6C4 is a 12-byte constant {0,0x60,0} passed BY VALUE to
 * the header child's v2C, not a dead pointer-to-member copy. The older header below is superseded there.
 * Is the mr/li instruction the only difference? NO: besides `li r28,0; mr r31,r28` (original) vs `li; li`,
 * one `neg` is scheduled a slot apart and the constants of the 0x48 info-box constructor are materialised
 * in another order (stores in the original order). Functionally equal.
 */
/* WIP (round 19, zero-idiom family): complete draft for the port, class `other` like its sibling.
   Generated from wip/r18i/fn_801F4850.cpp: same body, but only the selector (x50) is attached with
   fn_801E5448 here; the item box and the detail box are not. Same open points as the sibling
   (zero idiom before the sort loop, dead pointer-to-member copy, `li` scheduling in the info box). */
/* fn_801F2954: builds the three widgets of an item-list screen (a 0x7c selector, the 0x13c
   twelve-list item box with its 0x50 header child, and the 0x48 detail box), then fills the
   item box from the two unit lists and the convoy. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void fn_801E77E8(void*, int);
void fn_801F28F4(void* p, void* arg);
void fn_801F28C0(void* p, void* arg);
void fn_801FDAE0(void*);
void fn_801FDAF8(void*, int);
void fn_8028BFD8(void*, void*, void*, u32, u32);
void* memset(void*, int, u32);
int fn_8002460C(void);
int fn_8011B77C(void*, void*);
u32* fn_801116B8(void*);
int fn_80060754(void*);
int* fn_801059B0(void);
void fn_801FDC38(void*, void*);
extern u8* lbl_803CA870[];
extern u8 lbl_803CAB38[];
extern void* lbl_804CA4E8;
extern u8 lbl_8038CDE8[], lbl_8038DD34[], lbl_8038DCD0[], lbl_8038DCA0[], lbl_8038DC70[], lbl_8038DC40[];
struct T3 { int a[3]; };
extern T3 lbl_803741A8;
}
struct El { int size; void* prev; void* next; void clear(); };
typedef void (El::*PMF)();
extern "C" PMF lbl_8038D6B8;
extern "C" T3 lbl_8038D6C4;
class VA3 { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(T3); };

struct CB { void* f; int a; };
struct LNv { LNv* prev; LNv* next; int val[2]; };
struct RG { int size; LNv* prev; LNv* next; };
class Wv { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(void*, void*); };
class Wa { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(void*); };

struct L7C { WF w; int a40; LN l44; u8 a4c, a4d, a4e; u8 p4f[5]; s16 a54, a56, a58; u8 p5a[2]; int a5c, a60; u8 p64[4]; u8 a68; u8 p69[0xb]; int a74; u8 p78[4]; };
struct L50 { WF w; int a40; T3 a44; };
struct M13C {
    WF w; int a40; LN l44; int a4c; u8 a50, a51, a52; u8 p53; f32 a54;
    u8 a58[0x18]; s16 cur[12]; s16 a88; s16 a8a, a8c, a8e; f32 a90; s16 a94, a96;
    El l[12]; u8 p128[8]; CB cb; L50* a138;
};
struct G48 { WF w; int a40; int a44; };
struct Lsel { u8 p[0x52]; s16 a52, a54; u8 p56[0x1a]; u32 a70; u8 p74[8]; CB cb; };
struct Sc { u8 p[0x40]; Lsel* x40; u8 p44[0xc]; L7C* x50; M13C* x54; G48* x58; };
struct Units { u8* h0; u8 p[0x38]; u8* h3c; };
struct EC { u8 c; EC() { c = 0; } };

static inline LNv* adv(LNv* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
static inline int* curVal(M13C* m) {
    int i = ((Wv*)m)->v34();
    s16* c = &m->cur[i];
    RG* r = (RG*)&m->l[i];
    if (r->size == 0) return 0;
    return adv(r->next, *c)->val;
}
static inline void setCB(Lsel* l, void (*f)(void*, void*), int a) { l->cb.f = (void*)f; l->cb.a = a; }
static inline void setCB2(M13C* l, void (*f)(void*, void*), int a) { l->cb.f = (void*)f; l->cb.a = a; }
static inline void setI3(G48* h, int t) { h->a44 = t; if (t == 0) h->a40 = 0; }

struct MF { PMF f; MF(PMF p) : f(p) {} void operator()(El* e) const { (e->*f)(); } };
static inline void forEach(El* a, El* b, MF f) { for (; a != b; ++a) f(a); }

static inline void setPos(WF* w, s16 x, s16 y) {
    w->x1 = x + (s16)(w->x1 - w->x0);
    w->x0 = x;
    w->y1 = y + (s16)(w->y1 - w->y0);
    w->y0 = y;
}
static inline void setW(WF* w, s16 n) { w->x1 = w->x0 + n; }

static inline L7C* newSel() {
    L7C* o = (L7C*)fn_80079150(0x7c);
    if (o != NULL) {
        gInit((G40*)o, 0x18c, 0xc0, 0x296, 0x19c, 0x10a, 0xdc, 500, 0x10);
        o->w.vt = lbl_8038CDE8;
        o->a4c = 1; o->a4d = 0; o->a4e = 1;
        o->a54 = -0x8000; o->a56 = -0x8000; o->a58 = 0x1c;
        o->a5c = 0; o->a60 = 0; o->a68 = 0; o->a74 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline L50* newHead(M13C* m) {
    L50* o = (L50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0, 0, 0x11c, 0x20, 0x11c, 0x20, m->w.a26, 0x10);
        o->w.vt = lbl_8038DCA0;
        o->a40 = 0;
        o->a44 = lbl_803741A8;
        o->w.vt = lbl_8038DC70;
    }
    return o;
}
static inline void each0(MF f) {}
static inline M13C* newBox() {
    M13C* o = (M13C*)fn_80079150(0x13c);
    if (o != NULL) {
        gInit((G40*)o, 0x189, 0x64, 0x299, 0x13e, 0x110, 0xda, 0x1ea, 0x10);
        o->w.vt = lbl_8038DD34;
        o->a4c = 0;
        o->a50 = 0; o->a51 = 1; o->a52 = 0;
        o->a54 = 0.5f;
        o->a8a = -0x8000; o->a8c = -0x8000; o->a8e = 0;
        o->a90 = 0.0f;
        o->a94 = 0; o->a96 = 0;
        fn_8028BFD8(o->l, fn_801FDAE0, fn_801FDAF8, 0xc, 0xc);
        o->cb.f = 0;
        memset(o->a58, 0, 0x18);
        memset(o->cur, 0, 0x18);
        forEach(o->l, o->l + 12, MF(lbl_8038D6B8));
        o->w.vt = lbl_8038DCD0;
        ((Lst*)o)->v2C();
        o->a138 = newHead(o);
        setPos(&o->a138->w, -o->w.ix0, 4 - (s16)(o->a138->w.y1 - o->a138->w.y0));
        setW(&o->a138->w, (s16)(o->w.x1 - o->w.x0));
        o->a138->w.flags |= 0x10;
        ((VA3*)o->a138)->v2C(lbl_8038D6C4);
        fn_801E2F40(o, o->a138);
        o->w.tx = 0x12;
        o->w.ty = 8;
        o->a8e = 7;
    }
    return o;
}
static inline G48* newInfo() {
    G48* o = (G48*)fn_80079150(0x48);
    if (o != NULL) {
        WF* w = &o->w;
        w->rc = 0;
        w->vt = lbl_8038CB1C;
        w->id = -1;
        w->x0 = 0x197; w->y0 = 0x145; w->x1 = 0x289; w->y1 = 0x19d;
        w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
        w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
        w->a26 = 500; w->a28 = 0;
        w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
        w->flags = 0x10; w->a3c = 0;
        w->vt = lbl_8038DC40;
        o->a40 = 0;
        w->ix0 = 0; w->iy0 = 0; w->ix1 = 0xf2; w->iy1 = 0x58;
    }
    return o;
}
static inline BOOL usable(u8* u, int* it) {
    u8* g = lbl_803CA870[0];
    if (u == NULL) return TRUE;
    if (u == g) return FALSE;
    if (fn_8011B77C(*(u8**)(u + 0xf0) + 0x24, lbl_804CA4E8) && (fn_801116B8(it)[1] & 4)) return FALSE;
    return TRUE;
}
static inline void addUnits(M13C* m, u8* u) {
    for (; u != NULL; u = *(u8**)(u + 0xe8)) {
        int* it = (int*)(u + 0x1bc);
        for (int i = 0; i < 7; i++, it += 10) {
            if (it == NULL || *it == 0) break;
            if (usable(u, it)) ((Wv*)m)->v4C(it, u);
        }
    }
}
extern "C" void fn_801F2954(Sc* o) {
    Lsel* l = o->x40;
    l->a54 = l->a52;
    setCB(l, fn_801F28F4, *(int*)lbl_803CA870);
    if ((u32)l->a52 < l->a70 - 1) {
        s16 k = l->a52 + 1;
        if ((u32)k < l->a70) fn_801E77E8(l, k);
    } else {
        s16 k = l->a52 - 1;
        if (k >= 0) fn_801E77E8(l, k);
    }
    {
        L7C* p = newSel();
        o->x50 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x50->w.a28 = 8;
    o->x50->w.id = 0x104;
    ((Wa*)o->x50)->v34(fn_801E7A28(l));
    o->x50->a4c = 0;
    fn_801E5448(o, o->x50);
    {
        M13C* p = newBox();
        o->x54 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x54->w.id = 0x105;
    o->x54->w.a28 = 8;
    if (fn_8002460C() == 0) {
        addUnits(o->x54, ((Units*)lbl_804CB814)->h0);
    }
    addUnits(o->x54, ((Units*)lbl_804CB814)->h3c);
    if (fn_80060754(lbl_803CAB38)) {
        int* c = fn_801059B0();
        M13C* m = o->x54;
        for (int i = 0; i < c[0]; i++) {
            int* it = (int*)(c[1] + i * 0x28);
            if (it != NULL && *it != 0) ((Wv*)m)->v4C(it, 0);
        }
    }
    {
        M13C* m = o->x54;
        int i = 0;
        while (1) { EC e; fn_801FDC38((u8*)m + i * 0xc + 0x98, &e); if (++i == 12) break; }
    }
    setCB2(o->x54, fn_801F28C0, *(int*)lbl_803CA870);
    ((Wv*)o->x54)->v38();
    {
        G48* p = newInfo();
        o->x58 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x58->w.id = 0x109;
    o->x58->w.a28 = 8;
    if (curVal(o->x54)) {
        o->x58->a40 = curVal(o->x54)[1];
        setI3(o->x58, curVal(o->x54)[0]);
    } else {
        o->x58->a40 = 0;
        setI3(o->x58, 0);
    }
}
