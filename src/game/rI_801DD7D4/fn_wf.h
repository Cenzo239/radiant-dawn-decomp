#ifndef RI_WF_H
#define RI_WF_H
/* Widget base and common derived constructors, written as inlines. Field names are guesses. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
extern "C" {
void* fn_80079150(u32);
void fn_801E5448(void*, void*);
void* fn_801E7A28(void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E2F40(void*, void*);
extern u8 lbl_8038CB1C[], lbl_8038CAF0[], lbl_8038CD00[], lbl_8038F588[], lbl_8038C294[], lbl_8038C260[];
extern u8 lbl_8038C9C8[], lbl_8038F4F8[], lbl_8038F740[], lbl_8038F4C0[], lbl_8038F548[], lbl_8038CC9C[];
extern u8 lbl_8038FA04[], lbl_8038CAC0[];
extern void** lbl_804CB814;
}
struct WF {
    void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; f32 sx, sy, sz; u32 flags; void* a3c;
};
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->id = -1;
    w->x0 = x0; w->y0 = y0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}
struct LN { void* prev; void* next; };
struct G40 { WF w; int a40; LN l44; };
static inline void lnInit(LN* l) { l->next = l; l->prev = l; }
static inline void gInit(G40* g, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&g->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    g->w.vt = lbl_8038CAF0;
    g->a40 = 0;
    lnInit(&g->l44);
}
class Lst { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(); virtual int v38(void*); };
struct L84 { WF w; int a40; LN l44; int a4c; u8 a50, a51; s16 a52; u8 p54[2]; s16 a56, a58, a5a, a5c, a5e; f32 a60; s16 a64; u8 p66[0xa]; int a70; LN l74; void* a7c; int a80; void* a84; };
static inline void l84Init(L84* o, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    gInit((G40*)o, x0, y0, x1, y1, ix1, iy1, a26, fl);
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
struct Eff { void* vt; int a4; int a8; u8 ac, ad; u8 pe[6]; s16 a14; u8 p16[2]; f32 a18, a1c; u8 c[4]; f32 a24; };
struct L6C { WF w; void* a40; Eff e; };
static inline void l6cInit(L6C* o, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&o->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    o->w.vt = lbl_8038F588;
    Eff* m = &o->e;
    m->vt = lbl_8038C294;
    m->a4 = 0;
    m->a8 = 2;
    m->ac = 1;
    m->ad = 1;
    m->a14 = 0;
    m->a18 = 1.0f;
    m->a1c = 1.0f;
    m->c[0] = 0x80; m->c[1] = 0x80; m->c[2] = 0x80; m->c[3] = 0xff;
    m->a24 = 0.0f;
    ((VO0N*)m)->v0C();
    m->vt = lbl_8038C260;
    ((VO0N*)m)->v0C();
    ((Lst*)o)->v2C();
}
#endif
