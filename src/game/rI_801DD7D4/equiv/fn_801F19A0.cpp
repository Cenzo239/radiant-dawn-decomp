/* fn_801F19A0: builds the four widgets of a unit-list screen (0x84 unit list, 0x7c selector,
   0x50 caption, 0x50 detail box) and fills the list from both unit chains. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
int fn_8002460C(void);
void fn_801EA538(void*, void*);
void fn_801E5734(void*, void*);
extern u8 lbl_8038CDE8[], lbl_8038CA50[], lbl_8038CA18[], lbl_8038CEA8[];
extern char lbl_8036F03C[];
}
class VA { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(void*); };
struct L7C { WF w; int a40; LN l44; u8 a4c, a4d, a4e; u8 p4f[5]; s16 a54, a56, a58; u8 p5a[2]; int a5c, a60; u8 p64[4]; u8 a68; u8 p69[0xb]; int a74; u8 p78[4]; };
struct L50a { WF w; const char* a40; s16 a44; u8 a46; u8 p47[9]; };
struct L50b { WF w; int a40; u8 p44[8]; int a4c; };
struct Units { u8* h0; u8 p[0x38]; u8* h3c; };
struct Sc { u8 p[0x40]; L84* x40; L50b* x44; L50a* x48; L7C* x4c; };

static inline L84* newL() {
    L84* o = (L84*)fn_80079150(0x84);
    if (o != NULL) l84Init(o, 0, 0x1c, 0x260, 0xe4, 0x260, 0xc8, 0x226, 0x10);
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
        wfInit(&o->w, 0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1fe, 0x10);
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
        wfInit(&o->w, 0x12a, 0x124, 0x252, 0x194, 0x128, 0x70, 500, 0x10);
        o->w.vt = lbl_8038CEA8;
        o->a40 = 0;
        o->a4c = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline void addAll(VA* l, u8* n) { while (n != NULL) { l->v30(n); n = *(u8**)(n + 0xe8); } }
extern "C" void fn_801F19A0(Sc* o) {
    {
        L84* p = newL();
        o->x40 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x40->w.a28 = 8;
    o->x40->w.id = 0x100;
    if (fn_8002460C() == 0) addAll((VA*)o->x40, ((Units*)lbl_804CB814)->h0);
    addAll((VA*)o->x40, ((Units*)lbl_804CB814)->h3c);
    fn_801E5448(o, o->x40);
    {
        L7C* p = newN();
        o->x4c = p;
        if (p != NULL) p->w.rc++;
    }
    o->x4c->w.a28 = 8;
    o->x4c->w.id = 0x103;
    ((VA*)o->x4c)->v34(fn_801E7A28(o->x40));
    o->x4c->a4c = 0;
    fn_801E5448(o, o->x4c);
    {
        L50a* p = newC();
        o->x48 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x48->w.a28 = 8;
    o->x48->w.id = 0x102;
    o->x48->a40 = lbl_8036F03C + 1;
    fn_801E5448(o, o->x48);
    {
        L50b* p = newD();
        o->x44 = p;
        if (p != NULL) p->w.rc++;
    }
    o->x44->w.id = 0x101;
    o->x44->w.a28 = 8;
    fn_801EA538(o->x44, fn_801E7A28(o->x40));
    fn_801E5448(o, o->x44);
    fn_801E5734(o, o->x40);
}
