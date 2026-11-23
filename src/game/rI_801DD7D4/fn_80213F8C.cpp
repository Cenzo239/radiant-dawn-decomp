#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
void* fn_80079150(u32);
void fn_801E5448(void*, void*);
void* fn_801E7A28(void*);
void* fn_800CD204(int);
extern u8 lbl_8038CB1C[], lbl_8038CAF0[], lbl_8038CD00[], lbl_8038F588[], lbl_8038C294[], lbl_8038C260[];
extern u8 lbl_8038C9C8[], lbl_8038F4F8[], lbl_8038F740[], lbl_8038F4C0[];
void fn_80214618(void* p);
extern void** lbl_804CB814;
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
struct C4 { u8 r, g, b, a; };
struct L84 { WF w; int a40; LN l44; int a4c; u8 a50, a51; s16 a52; u8 p54[2]; s16 a56, a58, a5a, a5c, a5e; f32 a60; s16 a64; u8 p66[0xa]; int a70; LN l74; void* a7c; int a80; };
struct Eff { void* vt; int a4; int a8; u8 ac, ad; u8 pe[6]; s16 a14; u8 p16[2]; f32 a18, a1c; u8 c[4]; f32 a24; };
struct L6C { WF w; u8 p40[4]; Eff e; };
struct L54 { WF w; u8 c[4]; int a44; u8 p48[8]; int a50; };
struct L44 { WF w; void* a40; };
struct Sc { u8 p[0x44]; L84* a44; u8 p48[4]; L44* a4c; L54* a50; L44* a54; };
class Lst { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(); virtual int v38(void*); };
static inline void addAll(Lst* l, u8* u) { for (; u != NULL; u = *(u8**)(u + 0xe8)) l->v30(u); }
static inline void init2(L6C* o2) {
            wfInit(&o2->w, 0x20, 0xd8, 0x128, 0x17f, 0x108, 0xa7, 500, 0x10);
            o2->w.vt = lbl_8038F588;
            Eff* m = &o2->e;
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
            ((Lst*)o2)->v2C();
}
static inline L54* new3() {
 L54* o = (L54*)fn_80079150(0x54);
        if (o != NULL) {
            wfInit(&o->w, 0x12c, 0xcb, 0x260, 0xeb, 0x134, 0x20, 500, 0x10);
            o->w.vt = lbl_8038C9C8;
            o->c[0] = 0xff; o->c[1] = 0xff; o->c[2] = 0xff; o->c[3] = 0xff;
            o->a44 = 0;
            ((Lst*)o)->v2C();
            o->w.vt = lbl_8038F4F8;
            o->a50 = 0;
            ((Lst*)o)->v2C();
            ((Lst*)o)->v38(lbl_8038F740);
        }
 return o;
}
static inline L44* new4() {
 L44* o = (L44*)fn_80079150(0x54);
        if (o != NULL) {
            wfInit(&o->w, 0x12c, 0xf0, 0x248, 0x17c, 0x11c, 0x8c, 500, 0x10);
            o->w.vt = lbl_8038F4C0;
            o->a40 = 0;
            ((Lst*)o)->v2C();
        }
 return o;
}
void fn_80213F8C(Sc* s) {
/*P*/
    L84* o1;
    L6C* o2;
/*E*/
    {
        o1 = (L84*)fn_80079150(0x84);
        if (o1 != NULL) {
            gInit((G40*)o1, 0, 0x1c, 0x260, 0xe4, 0x260, 0xc8, 500, 0x10);
            o1->w.vt = lbl_8038CD00;
            o1->a4c = 0;
            o1->a50 = 1;
            o1->a51 = 0;
            o1->a52 = 0;
            o1->a56 = -0x8000;
            o1->a58 = -0x8000;
            o1->a5a = 0;
            o1->a5c = 3;
            o1->a5e = 0x1e;
            o1->a60 = 0.0f;
            o1->a64 = 0;
            o1->a70 = 0;
            {LN* l=&o1->l74; l->next = l; l->prev = l;}
            o1->a7c = 0;
            ((Lst*)o1)->v2C();
        }
        s->a44 = o1;
        if (o1 != NULL) o1->w.rc++;
    }
    s->a44->w.id = 0x81;
    s->a44->w.a28 = 8;
    {
        
        addAll((Lst*)s->a44, (u8*)lbl_804CB814[0]);
    }
    {
        
        addAll((Lst*)s->a44, (u8*)lbl_804CB814[0xf]);
    }
    {
        L84* l = s->a44;
        l->a7c = fn_80214618;
        l->a80 = 0;
    }
    fn_801E5448(s, s->a44);
    {
        o2 = (L6C*)fn_80079150(0x6c);
        if (o2 != NULL) {
init2(o2);
        }
        s->a4c = (L44*)o2;
        if (o2 != NULL) o2->w.rc++;
    }
    s->a4c->w.id = 0x83;
    s->a4c->w.a28 = 8;
    s->a4c->a40 = fn_801E7A28(s->a44);
    fn_801E5448(s, s->a4c);
    {
        L54* r = new3(); s->a50 = r; if (r != NULL) r->w.rc++;
    }
    s->a50->w.id = 0x87;
    {
        C4 c;
        C4* p = (C4*)fn_800CD204(0x1d);
        c.r = p->r; c.g = p->g; c.b = p->b; c.a = p->a;
        ((Lst*)s->a50)->v30(&c);
    }
    s->a50->w.a28 = 8;
    *(void**)&s->a50->a50 = fn_801E7A28(s->a44);
    fn_801E5448(s, s->a50);
    {
        L44* r = new4(); s->a54 = r; if (r != NULL) r->w.rc++;
    }
    s->a54->w.id = 0x86;
    s->a54->w.a28 = 8;
    s->a54->a40 = fn_801E7A28(s->a44);
    fn_801E5448(s, s->a54);
}
}
