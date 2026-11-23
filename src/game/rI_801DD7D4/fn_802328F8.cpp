#pragma auto_inline off
#pragma inline_max_size(20000)
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
extern u8 lbl_8038CDE8[], lbl_8038C9C8[], lbl_8038E758[], lbl_8038F494[], lbl_8038CEA8[], lbl_8038E120[];
void* fn_800CD204(int);
struct C4 { u8 r, g, b, a; };
struct L44 { WF w; void* a40; };
struct L50 { WF w; u8 c[4]; int a44; u8 p48[8]; };
struct L7C { WF w; int a40; LN l44; u8 a4c, a4d, a4e; u8 p4f[5]; s16 a54, a56, a58; u8 p5a[2]; int a5c, a60; u8 p64[4]; u8 a68; u8 p69[0xb]; int a74; };
class VA { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(int); virtual int v38(void*); };
static inline void g2(G40* g, LN* q,  s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&g->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    g->w.vt = lbl_8038CAF0;
    g->a40 = 0;
    q->next = q; q->prev = q;
}
static inline void l84b(L84* o, LN* l, LN* l2,  s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    g2((G40*)o, l, x0, y0, x1, y1, ix1, iy1, a26, fl);
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
    l2->next = l2; l2->prev = l2;
    o->a7c = 0;
    ((Lst*)o)->v2C();
}
static inline L44* newA() {
    L44* o = (L44*)fn_80079150(0x44);
    if (o != NULL) {
        wfInit(&o->w, 0x15c, 0x13, 0x23c, 0x3b, 0xe0, 0x28, 100, 0x10);
        o->w.vt = lbl_8038E120;
        o->a40 = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline L84* newL(LN*& s, LN*& s2) {
    L84* o = (L84*)fn_80079150(0x84);
    if (o != NULL) { s=&o->l44;s2=&o->l74; l84b(o, s,s2, 0, -0x24, 0x260, 0xa4, 0x260, 0xc8, 0x226, 0x10); }
    return o;
}
static inline L7C* newN(LN*& s3) {
    L7C* o = (L7C*)fn_80079150(0x7c);
    if (o != NULL) {
        s3 = &((G40*)o)->l44; g2((G40*)o, s3, -0x34, 0xc0, 0xd6, 0x19c, 0x10a, 0xdc, 500, 0x10);
        o->w.vt = lbl_8038CDE8;
        o->a4c = 1; o->a4d = 0; o->a4e = 1;
        o->a54 = -0x8000; o->a56 = -0x8000; o->a58 = 0x1c;
        o->a5c = 0; o->a60 = 0; o->a68 = 0; o->a74 = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline L50* newC() {
    L50* o = (L50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x1a4, 0xca, 0x2b4, 0x10a, 0x110, 0x40, 0x1fe, 0x10);
        o->w.vt = lbl_8038C9C8;
        o->c[0] = 0xff; o->c[1] = 0xff; o->c[2] = 0xff; o->c[3] = 0xff;
        o->a44 = 0;
        ((VA*)o)->v2C();
        o->w.vt = lbl_8038E758;
        ((VA*)o)->v38(lbl_8038F494);
    }
    return o;
}
static inline L50* newD() {
    L50* o = (L50*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x17e, 0x124, 0x2a6, 0x194, 0x128, 0x70, 500, 0x10);
        o->w.vt = lbl_8038CEA8;
        *(int*)o->c = 0;
        *(int*)&o->p48[4] = 0;
        ((VA*)o)->v2C();
    }
    return o;
}
static inline void addAll(VA* l, u8* n) { while (n != NULL) { l->v30(n); n = *(u8**)(n + 0xe8); } }
struct S28 { u8 p[0x70]; S28* a70; u8 p74[8]; L44* a7c; u8 p80[8]; u8* a88; };
void fn_802328F8(S28* o) {
    /*P*/
    L7C* n;
    L50* c;
    LN* s;
    LN* s2;
    LN* s3;
    L44* a;
    void* k;
    L84* l;
/*E*/
    {
        k = o->a70->a70;
        a = newA();
        o->a7c = a;
        if (a != NULL) a->w.rc++;
        o->a7c->w.id = 0xa;
        o->a7c->w.a28 = 4;
        o->a7c->w.sy = 0.0f;
        o->a7c->a40 = k;
    }
    l = newL(s, s2);
    l->w.id = 6;
    l->w.a28 = 8;
    addAll((VA*)l, (u8*)lbl_804CB814[0]);
    addAll((VA*)l, (u8*)lbl_804CB814[0xf]);
    l->a50 = 0;
    fn_801E5448(o, l);
    n = newN(s3);
    n->w.id = 7;
    n->w.a28 = 8;
    ((VA*)n)->v34((int)fn_801E7A28(l));
    n->a4c = 0;
    n->a68 = 0;
    n->a4e = 1;
    fn_801E5448(o, n);
    if (fn_80060754(lbl_803CAB38) != 0) {
        c = newC();
        c->w.id = 9;
        {
            C4 k;
            C4* p = (C4*)fn_800CD204(0x1d);
            k.r = p->r; k.g = p->g; k.b = p->b; k.a = p->a;
            ((VA*)c)->v30(&k);
        }
        c->w.a28 = 8;
        fn_801E5448(o, c);
    }
    c = newD();
    c->w.id = 8;
    c->w.a28 = 8;
    fn_801EA538(c, fn_801E7A28(l));
    fn_801E5448(o, c);
    {
        void* v = *(void**)(o->a88 + 0x90);
        W* h = fn_801E5640(o, -0x1000, 0);
        if (h != NULL) h->x64 = (const char*)v;
    }
}
}
