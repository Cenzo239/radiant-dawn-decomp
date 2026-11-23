#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
extern u8 lbl_8038E0A8[];
}
struct XY { s16 x, y; };
struct LN2 { LN2* prev; LN2* next; int val[2]; };
struct RG { int size; LN2* prev; LN2* next; };
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); };
struct SS { u8 p[0x68]; s16 cur[12]; u8 p80[8]; RG l[12]; };
struct Ctx { u8 p[0x28]; int x28; };
struct Sc { u8 p[0x40]; W* x40; u8 p44[4]; Ctx* x48; };
struct G48 { WF w; int a40; int a44; };
static inline LN2* adv(LN2* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
static inline int* curVal(W* b) {
    int i = b->v34();
    SS* s = (SS*)b;
    s16* c = &s->cur[i];
    RG* r = &s->l[i];
    if (r->size == 0) return 0;
    return adv(r->next, *c)->val;
}
static inline void setXb(void* o, void* w, s16 x, int f) { s16 yy = ((WF*)w)->y0; XY t; t.x = x; t.y = yy; fn_801E459C(o, w, &t, f); }
extern "C" void fn_8020291C(Sc* o) {
    G48* g;
    W* b = (W*)fn_801E5640(o, 0, 0);
    if (b == 0) {
        b = o->x40;
        fn_801E5448(o, b);
    }
    if (((WF*)b)->x0 != 0xe0) setXb(o, b, 0xe0, 0);
    if (fn_801E5640(o, 2, 0) == 0) {
        g = (G48*)fn_80079150(0x48);
        if (g) {
            wfInit(&g->w, 0x144, 0x130, 0x284, 0x190, 0x140, 0x60, 0x1f4, 0x10);
            g->w.vt = lbl_8038E0A8;
            g->a40 = 0;
            g->a44 = 0;
            ((Lst*)g)->v2C();
        }
        g->w.id = 2;
        g->w.a28 = 8;
        if (curVal(b)) {
            g->a40 = curVal(b)[1];
            g->a44 = curVal(b)[0];
        }
        fn_801E5448(o, g);
        setXb(o, g, 0xf0, 0);
    }
    fn_801E5734(o, b);
    {
    int s = o->x48->x28;
    void* w = fn_801E5640(o, -0x1000, 0);
    if (w) *(int*)((u8*)w + 0x64) = s;
    }
}
