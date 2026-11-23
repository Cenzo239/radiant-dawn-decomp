/* fn_801F8798 (0x898): builds the widgets of the convoy unit-select screen: the unit list (0x84, id 0x100,
 * starts above the screen with sz 0.5), the selector (0x7c, id 0x103, callback fn_801F7F28), a caption
 * (0x50, id 0x102), a detail box (0x50, id 0x101) and two info panels (0x58 id 0x107, 0x50 id 0x108).
 * Sibling of fn_801F19A0. Class `regs` (round 20): same instructions, order and references.
 * Note: this function was listed with the zero-idiom family in earlier notes, but it contains no list
 * sort and no `mr rZ,rI` idiom.
 * Caveat: constructors are inlines over plain structs (fn_wf.h); the two info panels are used without a
 * null check after allocation, as in the original. */
/* (declarations shared with fn_801F19A0): builds the four widgets of a unit-list screen (0x84 unit list, 0x7c selector,
   0x50 caption, 0x50 detail box) and fills the list from both unit chains. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
int fn_8002460C(void);
void fn_801EA538(void*, void*);
void fn_801E5734(void*, void*);
extern u8 lbl_8038CDE8[], lbl_8038CA50[], lbl_8038CA18[], lbl_8038CEA8[], lbl_8038CE68[], lbl_8038CE30[];
extern u8 lbl_803CA870[];
void fn_801E7938(void*, void*);
void fn_801F7F28(void* p, void* arg);
void* fn_801E5640(void*, int, int);
extern char lbl_8036F03C[];
}
class VA { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(void*); };
struct L7C { WF w; int a40; LN l44; u8 a4c, a4d, a4e; u8 p4f; s16 a50; u8 p52[2]; s16 a54, a56, a58; u8 p5a[2]; int a5c, a60; u8 p64[4]; u8 a68; u8 p69[0xb]; void* a74; void* a78; };
struct L50a { WF w; const char* a40; s16 a44; u8 a46; u8 p47[9]; };
struct L50b { WF w; int a40; u8 p44[8]; int a4c; };
struct Units { u8* h0; u8 p[0x38]; u8* h3c; };
struct Sc { u8 p[0x40]; L84* x40; L50b* x44; L50a* x48; L7C* x4c; };

struct K58 { WF w; void* a40; u8 a44; u8 a45[8]; };
struct K50 { WF w; void* a40; u8 a44; };
struct HH { u8 p[0x64]; const char* a64; };
static inline L84* newL() {
    L84* o = (L84*)fn_80079150(0x84);
    if (o != NULL) l84Init(o, 0, -0x32, 0x260, 0x96, 0x260, 0xc8, 0x226, 0x10);
    return o;
}
static inline L7C* newN() {
    L7C* o = (L7C*)fn_80079150(0x7c);
    if (o != NULL) {
        gInit((G40*)o, 0x20, 0xc0, 0x12a, 0x19c, 0x10a, 0xdc, 500, 0x10);
        o->w.vt = lbl_8038CDE8;
        o->a4c = 1; o->a4d = 0; o->a4e = 1;
        o->a54 = -0x8000; o->a56 = -0x8000; o->a58 = 0x1c;
        o->a5c = 0; o->a60 = 0; o->a68 = 0; o->a74 = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline L50a* newC() {
    L50a* o = (L50a*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x10, -0x2d, 0x250, -5, 0x240, 0x28, 0x1fe, 0x10);
        o->w.vt = lbl_8038CA50;
        o->a40 = 0;
        o->a44 = 0x20;
        o->a46 = 0;
        ((VA*)o)->v2C();
        o->w.vt = lbl_8038CA18;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline L50b* newD() {
    L50b* o = (L50b*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x17e, 0x12a, 0x2a6, 0x19a, 0x128, 0x70, 500, 0x10);
        o->w.vt = lbl_8038CEA8;
        o->a40 = 0;
        o->a4c = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline K58* newK58(void) {
    K58* o = (K58*)fn_80079150(0x58);
    if (o != NULL) {
        wfInit(&o->w, 0x13d, 0x50, 0x23d, 0x12c, 0x100, 0xdc, 500, 0x10);
        o->w.vt = lbl_8038CE68;
        o->a40 = 0;
        o->a44 = 0;
        o->a45[7] = 0; o->a45[6] = 0; o->a45[5] = 0; o->a45[4] = 0; o->a45[3] = 0; o->a45[2] = 0; o->a45[1] = 0; o->a45[0] = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline K50* newK50(void) {
    K50* o = (K50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x131, 0x12d, 0x249, 0x19c, 0x118, 0x6f, 500, 0x10);
        o->w.vt = lbl_8038CE30;
        o->a40 = 0;
        o->a44 = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline void addAll(VA* l, u8* n) { while (n != NULL) { l->v30(n); n = *(u8**)(n + 0xe8); } }
static inline void setHelp(void* s, const char* const& t) {
    HH* h = (HH*)fn_801E5640(s, -0x1000, 0);
    if (h != NULL) h->a64 = t;
}
extern "C" void fn_801F8798(Sc* o) {
    void* g = *(void**)lbl_803CA870;
    {
        L84* p = newL();
        o->x40 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x40->w.a28 = 8;
    o->x40->w.id = 0x100;
    if (fn_8002460C() == 0) addAll((VA*)o->x40, ((Units*)lbl_804CB814)->h0);
    addAll((VA*)o->x40, ((Units*)lbl_804CB814)->h3c);
    fn_801E7938(o->x40, g);
    o->x40->w.sz = 0.5f;
    {
        L7C* p = newN();
        o->x4c = p;
        if (p != NULL) p->w.rc++;
    }
    o->x4c->w.a28 = 8;
    o->x4c->w.id = 0x103;
    ((VA*)o->x4c)->v34(fn_801E7A28(o->x40));
    o->x4c->a4c = 1;
    o->x4c->a68 = 1;
    o->x4c->a4e = 0;
    {
        L7C* l = o->x4c;
        l->a74 = (void*)fn_801F7F28;
        l->a78 = g;
    }
    o->x4c->a50 = ((int*)lbl_803CA870)[7];
    fn_801E5448(o, o->x4c);
    {
        L50a* p = newC();
        o->x48 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x48->w.a28 = 8;
    o->x48->w.id = 0x102;
    o->x48->a40 = lbl_8036F03C + 1;
    {
        L50b* p = newD();
        o->x44 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x44->w.id = 0x101;
    o->x44->w.a28 = 8;
    fn_801EA538(o->x44, fn_801E7A28(o->x40));
    {
        K58* k = newK58();
        k->w.id = 0x107;
        k->a40 = fn_801E7A28(o->x40);
        k->a44 = 1;
        k->w.a28 = 8;
        fn_801E5448(o, k);
    }
    {
        K50* k = newK50();
        k->w.id = 0x108;
        k->a44 = 0;
        k->a40 = fn_801E7A28(o->x40);
        k->w.a28 = 8;
        fn_801E5448(o, k);
    }
    fn_801E5734(o, o->x4c);
    setHelp(o, lbl_8036F03C + 0x15b);
}
