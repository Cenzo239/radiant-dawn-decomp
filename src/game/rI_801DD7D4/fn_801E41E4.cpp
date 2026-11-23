#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8038CB48[];
extern char lbl_8038CBA8[];
extern char lbl_8038CB88[];
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
#if TARGET_PC
/* Host: clang requires C++ linkage for templates (the file is inside extern "C") */
extern "C++" {
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
}
#else
template <class L, class N> class Gd {
public:
    L* list;
    N* node;
    ~Gd() { if (node != NULL) fn_80079210(node); }
};
#endif
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
struct Pt { u16 x, y; };
struct Ps { s16 x, y; };
typedef struct WT { void* vt; int rc; u8 p8[2]; s16 xa, xc, xe, x10; u8 p12[0x28 - 0x12]; s16 x28; u8 p2a[6]; f32 x30; } WT;
typedef struct Tw {
    u8 pad[0x28];
    s16 x28;
    u8 p2a[6];
    u8 x30;
    u8 p31[3];
    RList list;
    Ps from;
    Pt to;
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
static inline Pt ptSub(const Pt& a, const Ps& b) {
    Pt r = a;
    r.x = (s16)r.x - b.x;
    r.y = (s16)r.y - b.y;
    return r;
}
static inline void setP(WT* b, const Pt& n) {
    s16 nx = n.x;
    s16 ny = n.y;
    b->xe = nx + (s16)(b->xe - b->xa);
    b->xa = nx;
    b->x10 = ny + (s16)(b->x10 - b->xc);
    b->xc = ny;
}
static inline f32 rate0(Tw* p) {
    f32 a = twBack(p)->x28 + 1;
    f32 b = p->x28 + 1;
    return 1.0f / a * (a - b);
}
/* The int locals stop the compiler reusing the conversions made in rate0. */
static inline f32 rate(Tw* p) {
    f32 r;
    int b0 = p->x28 + 1;
    int a0 = twBack(p)->x28 + 1;
    f32 a = a0;
    f32 b = b0;
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
    return r;
}
static inline void twScale(Tw* p, Pt& n, f32 e) {
    const Ps& cf = p->from;
    n.x = (s16)n.x * e;
    n.y = (s16)n.y * e;
    n.x = (s16)n.x + cf.x;
    n.y = (s16)n.y + cf.y;
    setP(twBack(p), n);
}
static inline void twApply(Tw* p, const Pt& v, f32 e) {
    Pt n = v;
    twScale(p, n, e);
}
Tw* fn_801E41E4(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CB48, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CB48, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    p->x48 = 0;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        Pt n = ptSub(p->to, p->from);
        const Ps& cf = p->from;
        n.x = (s16)n.x * e;
        n.y = (s16)n.y * e;
        n.x = (s16)n.x + cf.x;
        n.y = (s16)n.y + cf.y;
        setP(twBack(p), n);
    }
    twBack(p)->x30 = r;
    return p;
}
Tw* fn_801E459C(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CB48, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CB48, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    p->x48 = 1;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        Pt n = ptSub(p->to, p->from);
        const Ps& cf = p->from;
        n.x = (s16)n.x * e;
        n.y = (s16)n.y * e;
        n.x = (s16)n.x + cf.x;
        n.y = (s16)n.y + cf.y;
        setP(twBack(p), n);
    }
    twBack(p)->x30 = r;
    return p;
}
Tw* fn_801E495C(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CB48, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CB48, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    p->x48 = 2;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        Pt n = ptSub(p->to, p->from);
        const Ps& cf = p->from;
        n.x = (s16)n.x * e;
        n.y = (s16)n.y * e;
        n.x = (s16)n.x + cf.x;
        n.y = (s16)n.y + cf.y;
        setP(twBack(p), n);
    }
    twBack(p)->x30 = r;
    return p;
}
Tw* fn_801E59A8(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CBA8, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CBA8, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->x48 = 0;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        twApply(p, ptSub(p->to, p->from), e);
    }
    twBack(p)->x30 = r;
    return p;
}
Tw* fn_801E5D60(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CBA8, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CBA8, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->x48 = 1;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        twApply(p, ptSub(p->to, p->from), e);
    }
    twBack(p)->x30 = r;
    return p;
}
Tw* fn_801E6120(void* parent, RObj* w, const Ps* to, int block) {
    Tw* p;
    if (block) {
        p = (Tw*)fn_80081194(lbl_8038CBA8, parent);
    } else {
        p = (Tw*)fn_80081050(lbl_8038CBA8, parent);
    }
    twInit(p);
    rAdd(&p->list, w);
    p->x28 = ((WT*)w)->x28;
    p->x48 = 2;
    p->from.x = ((WT*)w)->xa;
    p->from.y = ((WT*)w)->xc;
    p->to.x = (s16)to->x;
    p->to.y = (s16)to->y;
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        twApply(p, ptSub(p->to, p->from), e);
    }
    twBack(p)->x30 = r;
    return p;
}
void fn_801E351C(Tw* p) {
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        Pt n = ptSub(p->to, p->from);
        const Ps& cf = p->from;
        n.x = (s16)n.x * e;
        n.y = (s16)n.y * e;
        n.x = (s16)n.x + cf.x;
        n.y = (s16)n.y + cf.y;
        setP(twBack(p), n);
    }
    twBack(p)->x30 = r;
}
void fn_801E64E0(Tw* p) {
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        Pt n = ptSub(p->to, p->from);
        const Ps& cf = p->from;
        n.x = (s16)n.x * e;
        n.y = (s16)n.y * e;
        n.x = (s16)n.x + cf.x;
        n.y = (s16)n.y + cf.y;
        setP(twBack(p), n);
    }
    twBack(p)->x30 = r;
}
struct Tf { u8 pad[0x28]; s16 x28; u8 p2a[6]; u8 x30; u8 p31[3]; RList list; f32 a40, a44; };
struct TfT { u8 pad[0x28]; s16 x28; u8 p2a[10]; f32 x34; u8 p38[4]; TfT* a3c; };
f32 fn_801E3468(TfT*);
void fn_801E5558(void*, void*, int);
static inline TfT* tfBack(Tf* p) {
    return p->list.size != 0 ? (TfT*)p->list.prev->val : NULL;
}
static inline f32 tfT(Tf* p) {
    f32 a = tfBack(p)->x28 + 1;
    f32 b = p->x28 + 1;
    return 1.0f / a * (a - b);
}
static inline f32 ease(f32 t, f32 a, f32 b) { return fn_8017F68C(0, a, b, t, 1.0f); }
static inline f32 ease2(f32 a, f32 b, f32 t) { return fn_8017F68C(0, a, b, t, 1.0f); }
static inline f32 ease3(Tf* p, f32 t) { return fn_8017F68C(0, p->a40, p->a44, t, 1.0f); }
static inline f32 ease4(Tf* p) { return fn_8017F68C(0, p->a40, p->a44, tfT(p), 1.0f); }
static inline void tfStep(Tf* p) {
    f32 v = ease2(p->a40, p->a44, tfT(p));
    tfBack(p)->x34 = v;
}
void fn_801E3E1C(Tf* p) {
    tfStep(p);
}
void fn_801E3EE0(Tf* p) {
    tfStep(p);
    if (p != NULL) {
        if (p != NULL) {
            listClear(&p->list);
            listFreeAll(&p->list);
        }
    }
}
Tf* fn_801E518C(void* parent, RObj* w, int block, f32 to) {
    Tf* p;
    if (block) {
        p = (Tf*)fn_80081194(lbl_8038CB88, parent);
    } else {
        p = (Tf*)fn_80081050(lbl_8038CB88, parent);
    }
    twInit((Tw*)p);
    rAdd(&p->list, w);
    p->x28 = ((TfT*)w)->x28;
    {
        TfT* w1 = (TfT*)w;
        f32 v = w1->x34;
        if (w1->a3c != NULL) {
            TfT* w2 = w1->a3c;
            f32 v2 = w2->x34;
            if (w2->a3c != NULL) {
                TfT* w3 = w2->a3c;
                f32 v3 = w3->x34;
                if (w3->a3c != NULL) {
                    TfT* w4 = w3->a3c;
                    f32 v4 = w4->x34;
                    if (w4->a3c != NULL) {
                        v4 *= fn_801E3468(w4->a3c);
                    }
                    v3 *= v4;
                }
                v2 *= v3;
            }
            v *= v2;
        }
        p->a40 = v;
    }
    p->a44 = to;
    {
    tfStep(p);
    }
    return p;
}
static inline void setQ(WT* b, const Ps& n) {
    b->xe = n.x + (s16)(b->xe - b->xa);
    b->xa = n.x;
    b->x10 = n.y + (s16)(b->x10 - b->xc);
    b->xc = n.y;
}
void fn_801E3778(Tw* p) {
    void* owner = *(void**)((u8*)p + 0x18);
    {
    WT* b = twBack(p);
    {
    s16 nx = p->to.x;
    b->xe = nx + (s16)(b->xe - b->xa);
    b->xa = nx;
    }
    {
    s16 ny = p->to.y;
    b->x10 = ny + (s16)(b->x10 - b->xc);
    b->xc = ny;
    }
    }
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        twApply(p, ptSub(p->to, p->from), e);
    }
    twBack(p)->x30 = r;
    if (p->x48 == 2) {
        fn_801E5558(owner, twBack(p), 1);
    }
    if (p != NULL) {
        if (p != NULL) {
            listClear(&p->list);
            listFreeAll(&p->list);
        }
    }
}
void fn_801E673C(Tw* p) {
    f32 t = rate0(p);
    f32 r = rate(p);
    {
        f32 e = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
        twApply(p, ptSub(p->to, p->from), e);
    }
    twBack(p)->x30 = r;
    if (p != NULL) {
        if (p != NULL) {
            listClear(&p->list);
            listFreeAll(&p->list);
        }
    }
}
struct Tb { u8 pad[0x18]; void* owner; u8 p1c[0xc]; s16 x28; u8 p2a[6]; u8 x30; u8 p31[3]; RList list; int mode; };
static inline WT* tbBack(Tb* p) {
    return p->list.size != 0 ? (WT*)p->list.prev->val : NULL;
}
static inline f32 tbRate(Tb* p) {
    f32 r;
    f32 b;
    f32 a;
    a = tbBack(p)->x28 + 1;
    b = p->x28 + 1;
    switch (p->mode) {
    case 0:
        r = 1.0f / a * (a - b);
        break;
    case 1:
        r = 1.0f / a * b;
        break;
    }
    return r;
}
void fn_801E3C18(Tb* p) {
    void* owner = p->owner;
    tbBack(p)->x30 = tbRate(p);
    if (p->mode == 1) {
        fn_801E5558(owner, tbBack(p), 1);
    }
    if (p != NULL) {
        if (p != NULL) {
            listClear(&p->list);
            listFreeAll(&p->list);
        }
    }
}
}
