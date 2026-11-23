#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma use_lmw_stmw on
#pragma auto_inline off
inline void* operator new(unsigned long, void* p) { return p; }
extern "C" {
void fn_80011CBC(void*, void*);
extern char fn_80006EE0[];
extern char lbl_8038CDCC[];
class HV {
public:
    void* val; void* h;
    HV(void* v) { val = v; h = 0; }
    HV(const HV& o) { val = o.val; h = 0; }
    ~HV() { if (h != NULL) fn_80011CBC(fn_80006EE0, h); }
};
typedef struct HNode { struct HNode* prev; struct HNode* next; HV val; } HNode;
typedef struct HList { int size; HNode* prev; HNode* next; } HList;
typedef struct Menu { u8 p[0x52]; s16 x52; u8 p54[0x1c]; HList list; } Menu;
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
static inline HNode* hAlloc() {
    HNode* n = (HNode*)fn_80079150(0x10);
    if (n == NULL) {
        fn_80290B48(__files + 0xa0, lbl_8038CDCC);
        fn_80291BD0();
    }
    return n;
}
static inline void hPush(HList* l, HNode* const& e, const HV& v) {
    HNode* n = hAlloc();
    Gd<HList, HNode> g;
    g.list = (HList*)&l->prev;
    g.node = n;
    {
        HV* p = &g.node->val;
        new (p) HV(v);
    }
    g.node = NULL;
    e->prev->next = n;
    n->prev = e->prev;
    e->prev = n;
    n->next = e;
    l->size++;
}
void fn_801E75B0(Menu* o, void* v) {
    HV x(v);
    HNode* e = (HNode*)&o->list.prev;
    hPush(&o->list, e, x);
}
struct Eq { int pad; const HV* v; Eq(const HV& h) { v = &h; } };
void fn_801E8D60(HList*, Eq);
static inline void hRem(HList* l, const HV& x) { fn_801E8D60(l, Eq(x)); }
static inline void hRem2(HList* l, const HV& x) { Eq e(x); fn_801E8D60(l, e); }
static inline void hRem3(HList* l, Eq e) { fn_801E8D60(l, e); }
void fn_801E769C(Menu* o, void* v) {
    {
        HV x(v);
        {Eq e(x); fn_801E8D60(&o->list, e);}
    }
    if ((u32)o->x52 >= o->list.size) {
        o->x52 = o->list.size != 0 ? o->list.size - 1 : 0;
    }
}

static inline HNode* hErase(HList* l, HNode* it, HNode* j) {
    if (it == j) return j;
    HNode* last = j->prev;
    it->prev->next = last->next;
    last->next->prev = it->prev;
    while (it != j) {
        HV* p = &it->val;
        p->~HV();
        HNode* t = it;
        it = it->next;
        fn_80079210(t);
        l->size--;
    }
    return j;
}
void fn_801E8D60(HList* l, Eq e) {
    HNode* end = (HNode*)&l->prev;
    HNode* it = l->next;
    while (it != end) {
        if (it->val.val == e.v->val) {
            HNode* j = it->next;
            while (j != end) {
                if (j->val.val != e.v->val) break;
                j = j->next;
            }
            it = hErase(l, it, j);
            if (it == end) break;
        }
        it = it->next;
    }
}
extern char lbl_8036EE94[];
void* fn_8024BC94(void);
#if TARGET_PC
FE10_PROTO void fn_8024519C(void*, p32arg);
#else
void fn_8024519C(void*, int);
#endif
void* fn_80076F54(const char*);
void fn_801E74CC(void) {
    
    u8* e;
    void* s;
    int* p;
    u32 n;
    u32 i;
    u32 n2;
    u32 i2;

    s = fn_8024BC94();
    p = (int*)fn_80076F54(lbl_8036EE94 + 0xf);
    if (p != NULL) {
        n = *p;
        e = (u8*)(p + 1);
        for (i = 0; i < n; i++, e += 0x30) {
            fn_8024519C(s, *(int*)(e + 0xc));
        }
    }
    p = (int*)fn_80076F54(lbl_8036EE94 + 0x1e);
    if (p != NULL) {
        n2 = *p;
        e = (u8*)(p + 1);
        for (i2 = 0; i2 < n2; i2++, e += 0x2c) {
            fn_8024519C(s, *(int*)(e + 0x20));
            fn_8024519C(s, *(int*)(e + 0x24));
            fn_8024519C(s, *(int*)(e + 0x28));
        }
    }
}
}
