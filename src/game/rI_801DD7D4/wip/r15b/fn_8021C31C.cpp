#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
int* fn_80077064(const char*);
void fn_80089BFC(void*);
void fn_80089BDC(void*);
u32 fn_80089C1C(void);
u32 fn_80089ED0(void);
extern char lbl_80371974[];
extern u8 lbl_803CAB38[];
extern u8 lbl_8038F868[];
struct Card { u8 p[8]; u8 a8; u8 p9[3]; };
struct W4C { WF w; s8 a40; f32 a44; void* a48; };
class SC { public: virtual int v08(); virtual int v0C(void*, int); };
struct SO { WF w; u8 p40[0xc]; W4C* a4c[5]; u8 p60; s8 a61; u8 a62[1]; };
static inline void wfI(WF* w, s16 x, s16 a26) { wfInit(w, x, 0, x + 0x78, 0xb6, 0x78, 0xb6, a26, 0x10); }
static inline W4C* newC(SO* o, s16 x) {
    W4C* c = (W4C*)fn_80079150(0x4c);
    if (c != NULL) {
        wfI(&c->w, x, o->w.a26 - 1);
        c->w.vt = lbl_8038F868;
        c->a40 = -1;
        c->a44 = 0.0f;
        c->a48 = fn_80079150(0xc);
        ((Lst*)c)->v2C();
    }
    return c;
}
struct CD { int n; Card c[1]; };
static inline Card* at(CD* d, int i) { return &d->c[i]; }
static inline Card* at2(CD* d, int i) { Card* c = d->c; return &c[i]; }
static inline Card* at3(CD* d, int i) { return (Card*)((char*)d + 4) + i; }
static inline CD* cd() { return (CD*)fn_80077064(lbl_80371974 + 0x17d); }
void fn_8021C31C(SO* o) {
    u8 st[4];
/*P*/
    s8 n;
    u8 r;
    u8 sum;
    int xo;
    int sel;
    int k;
    s8 i;
    W4C* c;
/*E*/
    int h=o->w.y1-o->w.y0; s16 ww=o->w.x1-o->w.x0; o->w.ix0 = 0; o->w.iy0 = 0; o->w.ix1 = ww; o->w.tx = 0; o->w.ty = 0; o->w.iy1 = h; o->w.a1c = (s16)h >> 1; o->w.a1a = (s16)ww >> 1;
    n = *fn_80077064(lbl_80371974 + 0x17d);
    fn_80089BFC(st);
    fn_80089BDC(lbl_803CAB38 + 0x94);
    r = fn_80089C1C();
    sum = 0;
    o->a61 = sum;
    for (i = 0; i < n; i++) {
        {Card* q=(Card*)((char*)cd()+4); q+=i; sum = sum + q->a8;}
        if (r < sum) { o->a61 = i; break; }
    }
    fn_80089BFC(o->a62);
    fn_80089BDC(st);
    sel = fn_80089ED0() % 5;
    xo = 0;
    for (k = 0; k < 5; k++, xo += 0x78) {
        if (o->a4c[k] != NULL) ((SC*)o)->v0C(o->a4c[k], 0);
        c = newC(o, xo);
        o->a4c[k] = c;
        c->w.a28 = 8;
        o->a4c[k]->w.sy = 0.0f;
        if (k == sel) {
            o->a4c[k]->a40 = o->a61;
        } else {
            s8 v;
            do {
                v = fn_80089ED0() % (u32)n;
                if (v == o->a61) {
                    v = -1;
                } else {
                    for (int j = 0; j < k; j++) {
                        if (v == o->a4c[j]->a40) { v = -1; break; }
                    }
                }
            } while (v == -1);
            o->a4c[k]->a40 = v;
        }
        fn_801E2F40(o, o->a4c[k]);
    }
}
}
