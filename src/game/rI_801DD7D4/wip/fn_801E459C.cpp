// Round 8 attempt: 88 of 240 words, float block unfinished. See NOTES_round8_a.md.
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8038CB48[];
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
static inline void rPush(RList* l, LNode* const& e, RObj* c) {
    LNode* n = nodeAlloc();
    Gd<RList, LNode> g;
    g.list = (RList*)&l->prev;
    g.node = n;
    {
        RObj** p = &g.node->val;
        if (p != NULL) {
            *p = c;
        }
    }
    g.node = NULL;
    e->prev->next = n;
    n->prev = e->prev;
    e->prev = n;
    n->next = e;
    l->size++;
}
static inline void rAdd(RList* l, RObj* c) {
    if (c != NULL) {
        LNode* n = listFind(l, c);
        LNode* e = (LNode*)&l->prev;
        if (n == e) {
            rPush(l, e, c);
            if (c != NULL) {
                c->rc++;
            }
        }
    }
}

typedef struct WT { void* vt; int rc; u8 p8[2]; s16 xa, xc, xe, x10; u8 p12[0x28 - 0x12]; s16 x28; u8 p2a[6]; f32 x30; } WT;
typedef struct PtS { s16 x, y; } PtS;
typedef struct Tw {
    u8 pad[0x28];
    s16 x28;
    u8 p2a[6];
    u8 x30;
    u8 p31[3];
    RList list;
    s16 x40, x42;
    u16 x44, x46;
    int x48;
} Tw;
static inline void twInit(Tw* p) {
    if (p != NULL) {
        LNode* e;
        p->x30 = 0;
        e = (LNode*)&p->list.prev;
        p->list.size = 0;
        p->list.next = e;
        p->list.prev = e;
    }
}
static inline WT* twBack(Tw* p) {
    return p->list.size != 0 ? (WT*)p->list.prev->val : NULL;
}
static inline PtS mkPt(s16 x, s16 y) { PtS p; p.x = x; p.y = y; return p; }
static inline PtS lerpP(PtS v, f32 e, s16 ox, s16 oy) {
    f32 fy = v.y * e;
    f32 fx = v.x * e;
    v.x = (s16)fx + ox;
    v.y = (s16)fy + oy;
    return v;
}
static inline void setP(WT* b, PtS n) {
    s16 nx = n.x;
    s16 ny = n.y;
    b->xe = nx + (s16)(b->xe - b->xa);
    b->xa = nx;
    b->x10 = ny + (s16)(b->x10 - b->xc);
    b->xc = ny;
}
Tw* fn_801E459C(void* parent, RObj* w, const PtS* to, int block) {
    Tw* p;
    f32 r;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CB48, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CB48, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    {
        s16 tx = to->x;
        s16 ty = to->y;
        p->x40 = ((WT*)w)->xa;
        p->x42 = ((WT*)w)->xc;
        p->x44 = tx;
        p->x46 = ty;
    }
    p->x48 = 1;
    {
        f32 t;
        {
            f32 b;
            f32 a;
            a = twBack(p)->x28 + 1;
            b = p->x28 + 1;
            t = 1.0f / a * (a - b);
        }
        {
            f32 b;
            f32 a;
            b = p->x28 + 1;
            a = twBack(p)->x28 + 1;
            switch (p->x48) {
            case 0:
                r = 1.0f;
                break;
            case 1:
                r = 1.0f / a * (a - b);
                break;
            case 2:
                r = 1.0f / a * b;
                break;
            }
        }
        {
            f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
            u16 tx = p->x44;
            u16 ty = p->x46;
            s16 ox = p->x40;
            s16 oy = p->x42;
            PtS n = lerpP(mkPt((s16)tx - ox, (s16)ty - oy), e, ox, oy);
            setP(twBack(p), n);
        }
    }
    twBack(p)->x30 = r;
    return p;
}
}
