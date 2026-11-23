#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8038DE28[];
extern char lbl_8038D1E0[];
extern char lbl_8038D1C4[];
extern char lbl_8038D1A8[];
extern char lbl_8038CB48[];
extern char lbl_8038CB68[];
extern char lbl_8038CB88[];
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);

/* List insert: the guard holds the list and node; the value goes through the guard's node. */
typedef struct LN2 { struct LN2* prev; struct LN2* next; int a, b; } LN2;
typedef struct RL2 { int size; LN2* prev; LN2* next; } RL2;
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
struct V2 { int a, b; };
class LW {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44();
};
#define INS2(fn, base, nmax, str) \
typedef struct LW##fn { u8 pad[base]; RL2 l[1]; } LW##fn; \
static inline LN2* al##fn(void) { \
    LN2* n = (LN2*)fn_80079150(0x10); \
    if (n == NULL) { \
        fn_80290B48(__files + 0xa0, str); \
        fn_80291BD0(); \
    } \
    return n; \
} \
static inline void ins##fn(RL2* l, LN2* const& e, const V2& v) { \
    LN2* n = al##fn(); \
    Gd<RL2, LN2> g; \
    g.list = (RL2*)&l->prev; \
    g.node = n; \
    { \
        V2* p = (V2*)&g.node->a; \
        if (p != NULL) { \
            p->a = v.a; \
            p->b = v.b; \
        } \
    } \
    g.node = NULL; \
    e->prev->next = n; \
    n->prev = e->prev; \
    e->prev = n; \
    n->next = e; \
    l->size++; \
} \
void fn(LW* o, int a, int b) { \
    int k; \
    k = o->v44(); \
    if (k != nmax) { \
        V2 v; \
        RL2* l = &((LW##fn*)o)->l[k]; \
        LN2* e = (LN2*)&l->prev; \
        v.a = a; \
        v.b = b; \
        ins##fn(l, e, v); \
    } \
}
#pragma use_lmw_stmw on
INS2(fn_801ED010, 0x88, 9, lbl_8038D1E0)
INS2(fn_801EE018, 0x74, 4, lbl_8038D1C4)
INS2(fn_801EF020, 0x80, 7, lbl_8038D1A8)
INS2(fn_801FE938, 0x98, 0xd, lbl_8038DE28)
#pragma use_lmw_stmw off

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
typedef struct Seq { u8 pad[0x28]; s16 x28; u8 p2a[6]; u8 x30; u8 p31[3]; RList list; int x40; } Seq;
void fn_801E5448(Seq* o, RObj* c) {
    rAdd(&o->list, c);
}

void fn_801E5734(Seq* o, RObj* c) {
    if (c != NULL) {
        LNode* n = listFind(&o->list, c);
        if (n != (LNode*)&o->list.prev) {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            fn_80079210(n);
            o->list.size--;
            {
                LNode* e = (LNode*)&o->list.prev;
                rPush(&o->list, e, c);
            }
        }
    }
}

typedef struct WC { void* vt; int rc; u8 p8[2]; s16 xa, xc; u8 pe[0x1a - 0xe]; s16 x1a, x1c; u8 p1e[0x3c - 0x1e]; struct WC* x3c; int x40; RList l44; } WC;
typedef struct PtS { s16 x, y; } PtS;


typedef struct WT { void* vt; int rc; u8 p8[2]; s16 xa, xc, xe, x10; u8 p12[0x28 - 0x12]; s16 x28; u8 p2a[6]; f32 x30, x34; } WT;
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
typedef struct Fd {
    u8 pad[0x28];
    s16 x28;
    u8 p2a[6];
    u8 x30;
    u8 p31[3];
    RList list;
    int x40;
} Fd;
#define FADE(fn, cls, mode) \
Fd* fn(void* parent, RObj* w, int block) { \
    Fd* p; \
    f32 r; \
    if (block) { \
        p = (Fd*)fn_80081194(cls, parent); \
    } else { \
        p = (Fd*)fn_80081050(cls, parent); \
    } \
    twInit((Tw*)p); \
    rAdd(&p->list, w); \
    p->x28 = ((WT*)w)->x28; \
    p->x40 = mode; \
    { \
        f32 b; \
        f32 a; \
        a = twBack((Tw*)p)->x28 + 1; \
        b = p->x28 + 1; \
        switch (p->x40) { \
        case 0: \
            r = 1.0f / a * (a - b); \
            break; \
        case 1: \
            r = 1.0f / a * b; \
            break; \
        } \
    } \
    twBack((Tw*)p)->x30 = r; \
    return p; \
}
FADE(fn_801E4D1C, lbl_8038CB68, 0)
FADE(fn_801E4F50, lbl_8038CB68, 1)
}
