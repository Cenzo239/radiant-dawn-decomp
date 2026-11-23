#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
template <class L, class N> struct Gd { L* list; N* node; ~Gd() { if (node != NULL) fn_80079210(node); } };
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
struct LO { u8 p[0x74]; RList l; };
static inline void rAdd(RList* l, RObj* c) { LNode* n = listFind(l, c); LNode* e = (LNode*)&l->prev; if (n == e) rPush(l, e, c); }
static inline void rAdd2(RList* l, RObj* c) { LNode* e = (LNode*)&l->prev; LNode* n = listFind(l, c); if (n == e) rPush(l, e, c); }
extern "C" void fn_80223708(LO* o, RObj* c) {
    rAdd(&o->l, c);

}
