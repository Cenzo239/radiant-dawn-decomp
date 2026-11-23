/* fn_80225650 (0x620): builds the four widgets of a unit-list screen: the unit list (0x84, id 0x81, filled
 * from both unit chains of lbl_804CB814), an info panel (0x80, id 0x82), a small label (0x54, id 0x83) and
 * a 0x50 panel (id 0x84), each bound to the list's current entry. Sibling of fn_8021FA30.
 * Class `regs` (round 20): same instructions, order and references; registers differ.
 * Caveat: the constructors are inlines over plain structs with vtable stores by label (see fn_wf.h); the
 * real code is a class hierarchy with `new`. Field names are guesses. */
/* symcheck: (a) clean. Block 3 was a tool artefact: a dead temporary in r26 looked live at blr because `bl _restgpr_26` was not seen as reloading r26-r31 (fixed in symcheck). */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void fn_801EA538(void*, void*);
void fn_80225C70(void* p);
extern u8 lbl_8038FE60[], lbl_8038FB10[], lbl_8038CEA8[];
}
/* 0x80 list info panel */
struct P80 { WF w; int a40; LN l44; u8 a4c, a4d, a4e; u8 p4f[5]; s16 a54, a56, a58; u8 p5a[2]; int a5c; u8 a60; u8 p61[3]; int a64; s16 a68; u8 p6a[2]; f32 a6c; u8 p70[8]; int a78; int a7c; };
struct P54 { WF w; u8 c40[4]; int a44; u8 p48[8]; void* a50; };
struct P50 { WF w; int a40; u8 p44[8]; int a4c; };
struct Sc { u8 p[0x44]; L84* a44; P54* a48; P80* a4c; P50* a50; };
class L34 { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(void*); };
static inline void addAll(Lst* l, u8* u) { for (; u != NULL; u = *(u8**)(u + 0xe8)) l->v30(u); }
static inline L84* newL(void) {
    L84* o = (L84*)fn_80079150(0x84);
    if (o != NULL) {
        gInit((G40*)o, 0, 0x1c, 0x260, 0xe4, 0x260, 0xc8, 0x226, 0x10);
        o->w.vt = lbl_8038CD00;
        o->a4c = 0;
        o->a50 = 1;
        o->a51 = 0;
        o->a52 = 0;
        o->a56 = -0x8000;
        o->a58 = -0x8000;
        o->a5a = 0;
        o->a5c = 3;
        o->a5e = 0x1e;
        o->a60 = 0.0f;
        o->a64 = 0;
        o->a70 = 0;
        {LN* l = &o->l74; l->next = l; l->prev = l;}
        o->a7c = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline P80* new80(void) {
    P80* o = (P80*)fn_80079150(0x80);
    if (o != NULL) {
        gInit((G40*)o, 0x20, 0xc0, 0x12a, 0x19c, 0x10a, 0xdc, 0x1f4, 0x10);
        o->w.vt = lbl_8038FE60;
        o->a4c = 1;
        o->a4d = 0;
        o->a4e = 0;
        o->a54 = -0x8000;
        o->a56 = -0x8000;
        o->a58 = 0x21;
        o->a5c = 0;
        o->a60 = 0;
        o->a64 = 0;
        o->a68 = 0;
        o->a6c = 0.0f;
        o->a78 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline P54* new54(void) {
    P54* o = (P54*)fn_80079150(0x54);
    if (o != NULL) {
        wfInit(&o->w, 0x150, 0xe0, 0x260, 0x100, 0x110, 0x20, 0x1f4, 0x10);
        o->w.vt = lbl_8038C9C8;
        o->c40[0] = 0xff; o->c40[1] = 0xff; o->c40[2] = 0xff; o->c40[3] = 0xff;
        o->a44 = 0;
        ((Lst*)o)->v2C();
        o->w.vt = lbl_8038FB10;
        o->a50 = 0;
        o->w.tx = 0;
        o->w.ty = 0;
    }
    return o;
}
static inline P50* new50(void) {
    P50* o = (P50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x12a, 0x124, 0x252, 0x194, 0x128, 0x70, 0x1f4, 0x10);
        o->w.vt = lbl_8038CEA8;
        o->a40 = 0;
        o->a4c = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
extern "C" void fn_80225650(Sc* s) {
    {
        L84* o = newL();
        s->a44 = o;
        if (o != NULL) o->w.rc++;
    }
    s->a44->w.id = 0x81;
    s->a44->w.a28 = 8;
    s->a44->a50 = 0;
    addAll((Lst*)s->a44, (u8*)lbl_804CB814[0]);
    addAll((Lst*)s->a44, (u8*)lbl_804CB814[0xf]);
    {
        L84* l = s->a44;
        l->a7c = fn_80225C70;
        l->a80 = 0;
    }
    fn_801E5448(s, s->a44);
    {
        P80* r = new80();
        s->a4c = r;
        if (r != NULL) r->w.rc++;
    }
    s->a4c->w.id = 0x82;
    s->a4c->w.a28 = 8;
    s->a4c->a60 = 0;
    ((L34*)s->a4c)->v34(fn_801E7A28(s->a44));
    fn_801E5448(s, s->a4c);
    {
        P54* r = new54();
        s->a48 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a48->w.id = 0x83;
    s->a48->w.a28 = 8;
    s->a48->a50 = fn_801E7A28(s->a44);
    fn_801E5448(s, s->a48);
    {
        P50* r = new50();
        s->a50 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a50->w.id = 0x84;
    s->a50->w.a28 = 8;
    fn_801EA538(s->a50, fn_801E7A28(s->a44));
    fn_801E5448(s, s->a50);
}
