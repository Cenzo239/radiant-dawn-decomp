/* fn_801F9030 (0x74C), zero-idiom family, round 20: complete draft, class `other`.
 * Builds the convoy list screen: hides the top bar entry, slides widget 0x100 off screen, creates the
 * 12-category item list (0x13c bytes, id 0x105) with its header row, fills it from the convoy, sorts the
 * twelve category lists, then adds a title strip (0x40, id 0x10a) and an info panel (0x48, id 0x109).
 * Sibling of fn_80202344 (8 categories). 467 of 467 instructions.
 * Differences from the original (tools/equiv/dd.py, registers masked):
 *   1. the zero idiom before the sort loop: original `li r28,0; mr r31,r28; li r30,0`, ours three `li`;
 *   2. ours saves one more register (r25): the constant 0x110 for ix1 sits in a saved register where the
 *      original has it in r7, so `_savegpr_25/_restgpr_25` instead of `_26`;
 *   3. constant scheduling only: one `neg` in the header-row placement and the `li`/`lfs`/`addi`
 *      materialisation order inside the two small constructors (0x40 and 0x48 widgets) are in another
 *      order; the stores themselves are in the original order.
 * NOT only the mr/li instruction (items 2 and 3 are register/scheduling differences). Functionally equal.
 * Caveats: constructors are inlines over plain structs (fn_wf.h); when an allocation fails the original
 * still writes through the null pointer and so does this. lbl_8038D738 is a constant {0, 0x60, 0}. */
#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_8028BFD8(void*, void*, void*, int, int);
void fn_80204454(void* p);
void fn_801ECD88(void* p, void* arg);
void* memset(void*, int, u32);
extern u8 lbl_8038DD34[], lbl_8038DCD0[], lbl_8038DCA0[], lbl_8038DC70[], lbl_8038DC10[], lbl_8038DC40[];
extern u8 lbl_803CA870[];
void fn_801FDAE0(void* p);
void fn_801FDAF8(void* p, void* arg);
void fn_801F28C0(void* p, void* arg);
void fn_801FDC38(void*, void*);
void fn_801E495C(void*, void*, void*, int);
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
extern "C" MF lbl_8038D72C;
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
struct T3x { int a, b, c; };
extern "C" T3 lbl_8038D738;
struct XY { s16 x, y; };
class VM { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); };
/* 12-category sorted item list (0x13c) */
struct BB { WF w; int a40; LN l44; int x4c; u8 x50, x51, x52; f32 x54; u8 x58[0x18]; u8 x70[0x18]; u8 p88[2]; s16 x8a, x8c, x8e; f32 x90; s16 x94, x96; El arr[12]; u8 p128[8]; void* x130; void* x134; WF* x138; };
struct Nw { WF w; int a40; W3 a44; };
struct N40 { WF w; };
struct N48 { WF w; void* a40; void* a44; };
struct Bk { int n; u8* items; };
struct Item { int x0; u8 p4[0x24]; };
struct Top { u8 p[0x4e]; u8 x4e; u8 p4f[0x19]; u8 x68; };
struct Sc { u8 p[0x4c]; Top* x4c; u8 p50[4]; BB* x54; N48* x58; };
struct EC { u8 c; EC() { c = 0; } };
static inline void setXr(WF* w, s16 x) { w->x1 = x + (s16)(w->x1 - w->x0); w->x0 = x; }
static inline void setYr(WF* w, s16 y) { w->y1 = y + (s16)(w->y1 - w->y0); w->y0 = y; }
static inline int hgt(WF* w) { return (s16)(w->y1 - w->y0); }
static inline void mv(void* s, WF* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv3(void* s, WF* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void setB(N48* b, void* a, void* c) { b->a40 = a; b->a44 = c; if (!b->a44) b->a40 = 0; }
static inline void setCB(BB* b, void (*f)(void*, void*), void* k) { b->x130 = (void*)f; b->x134 = k; }
template <class T> static inline void mvR(void* s, T*& w, s16 x) { XY p; s16 y = ((WF*)w)->y0; p.x = x; p.y = y; fn_801E459C(s, w, &p, 0); }
static inline void setXY(WF* w, s16 x, s16 y) { setXr(w, x); setYr(w, y); }
static inline BB* mkB() {
    BB* b = (BB*)fn_80079150(0x13c);
    if (b) {
        gInit((G40*)b, 0x189, 0x64, 0x299, 0x13e, 0x110, 0xda, 0x1ea, 0x10);
        b->w.vt = lbl_8038DD34;
        b->x4c = 0;
        b->x50 = 0;
        b->x51 = 1;
        b->x52 = 0;
        b->x54 = 2.0f;
        b->x8a = -0x8000;
        b->x8c = -0x8000;
        b->x8e = 0;
        b->x90 = 0.0f;
        b->x94 = 0;
        b->x96 = 0;
        fn_8028BFD8(b->arr, fn_801FDAE0, fn_801FDAF8, 0xc, 0xc);
        b->x130 = 0;
        memset(b->x58, 0, 0x18);
        memset(b->x70, 0, 0x18);
        {
            FnE g;
            g.f = lbl_8038D72C;
            forEach(&b->arr[0], &b->arr[12], g);
        }
        b->w.vt = lbl_8038DCD0;
        ((Lst*)b)->v2C();
        {
            Nw* n = (Nw*)fn_80079150(0x50);
            if (n) {
                s16 a = b->w.a26;
                wfInit(&n->w, 0, 0, 0x11c, 0x20, 0x11c, 0x20, a, 0x10);
                n->w.vt = lbl_8038DCA0;
                n->a40 = 0;
                n->a44 = lbl_803741A8;
                n->w.vt = lbl_8038DC70;
            }
            b->x138 = &n->w;
        }
        {
            WF* w = b->x138;
            setXY(w, -b->w.ix0, 4 - hgt(w));
            b->x138->x1 = b->x138->x0 + (s16)(b->w.x1 - b->w.x0);
            b->x138->flags |= 0x10;
            ((VA*)b->x138)->v2C(lbl_8038D738);
            fn_801E2F40(b, b->x138);
            b->w.tx = 0x12;
            b->w.ty = 8;
            b->x8e = 7;
        }
    }
    return b;
}
static inline N40* mk40() {
    N40* n = (N40*)fn_80079150(0x40);
    if (n) {
        wfInit(&n->w, 0x31, 0x13, 0x231, 0x3b, 0, 0, 0xbe, 0x10);
        n->w.vt = lbl_8038DC10;
        n->w.ix0 = 0; n->w.iy0 = 0; n->w.ix1 = 0x200; n->w.iy1 = 0x28;
    }
    return n;
}
static inline N48* mk48() {
    N48* n = (N48*)fn_80079150(0x48);
    if (n) {
        wfInit(&n->w, 0x197, 0x145, 0x289, 0x19d, 0, 0, 0x1f4, 0x10);
        n->w.vt = lbl_8038DC40;
        n->a40 = 0;
        n->w.ix0 = 0; n->w.iy0 = 0; n->w.ix1 = 0xf2; n->w.iy1 = 0x58;
    }
    return n;
}
extern "C" void fn_801F9030(Sc* o) {
    { Top* t = o->x4c; t->x68 = 1; t->x4e = 0; }
    {
        WF* w = (WF*)fn_801E5640(o, 0x100, 0);
        if (w) mv3(o, w, w->x0, -0x24, 0);
    }
    {
        BB* b = mkB();
        o->x54 = b;
        if (b) b->w.rc++;
    }
    o->x54->w.id = 0x105;
    o->x54->w.a28 = 8;
    o->x54->x51 = 0;
    {
        Bk* c = (Bk*)fn_801059B0();
        VL* l = (VL*)o->x54;
        int k = 0;
        for (int i = 0; i < c->n; i++) {
            Item* it = (Item*)(c->items + k);
            if (it && it->x0) l->v4C(it, 0);
            k += 0x28;
        }
    }
    {
        BB* q = o->x54;
        int i = 0;
        while (1) { EC e; fn_801FDC38((u8*)q + i * 0xc + 0x98, &e); if (++i == 12) break; }
    }
    {
        setCB(o->x54, fn_801F28C0, *(void**)lbl_803CA870);
    }
    ((VM*)o->x54)->v38();
    fn_801E5448(o, o->x54);
    mvR(o, o->x54, 0x135);
    {
        N40* n = mk40();
        n->w.id = 0x10a;
        n->w.a28 = 8;
        fn_801E5448(o, n);
    }
    {
        N48* n = mk48();
        o->x58 = n;
        if (n) n->w.rc++;
    }
    o->x58->w.id = 0x109;
    o->x58->w.a28 = 8;
    o->x58->a40 = 0;
    { N48* b = o->x58; b->a44 = 0; b->a40 = 0; }
    fn_801E5448(o, o->x58);
    mvR(o, o->x58, 0x143);
}
