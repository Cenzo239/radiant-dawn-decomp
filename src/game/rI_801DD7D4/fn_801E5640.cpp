/* EXACT (round 23a): fn_801E5640, from equiv/fn_801E5640.cpp; same const W* parameter as fn_801E31D4 */
/* fn_801E5640 (0xF4): find a child widget by id, searching the child list (header at +0x34) back to front;
 * with `deep` set, each child's own find (vtable +0x10) is tried too. fn_801E31D4 and fn_801E5640 are the
 * same template code for two list offsets (+0x40 and +0x34).
 * Class `sched` (round 20). Moved instructions (read with tools/equiv/dd.py): the load of the list head
 * (`lwz r31,0x48(r3)`-style) and the load of rbegin()'s uninitialised scratch word are scheduled a few
 * instructions later in the prologue; both still precede every store and r3's reuse keeps its order.
 * Harmless.
 * RIt is MSL's reverse_iterator, which carries a scratch iterator (tmp) in front of the wrapped one;
 * operator* does tmp = current; --tmp. The scratch word is copied uninitialised, as in the original.
 * The copies flow outwards through return values (rbegin() temp -> returned temp -> `it`), which is what
 * gives the ascending stack slots. A port should use std::list::reverse_iterator. */
#include "game/rI_801DD7D4/types.h"
struct RObj;
struct LNode { LNode* prev; LNode* next; RObj* val; };
struct RObj {
    virtual void destroy(int);
    virtual int contains(RObj*, int);
    virtual RObj* find(int, int);
    int rc; s16 id;
};
struct It { LNode* p; };
/* MSL reverse_iterator: a scratch iterator in front of the wrapped one. */
struct RIt {
    It tmp; It cur;
    RIt() {}
    explicit RIt(It i) { cur = i; }
    
    
    RObj* operator*() { tmp = cur; tmp.p = tmp.p->prev; return tmp.p->val; }
    RIt& operator++() { cur.p = cur.p->prev; return *this; }
};
static inline bool ne(const RIt& a, const RIt& b) { return a.cur.p != b.cur.p; }
struct RList { int size; LNode* prev; LNode* next; };
struct W { u8 p[0x34]; RList list; };
static inline RIt rbegin(W* w) { It i; i.p = (LNode*)&w->list.prev; return RIt(i); }
static inline RIt rend(W* w) { It i; i.p = w->list.next; return RIt(i); }
extern "C" RObj* fn_801E5640(const W* wc, int id, int deep) { W* w = (W*)wc;
    RObj* r = NULL;
    RIt it = rbegin(w); RIt e = rend(w);
    for (; ne(it, e); ++it) {
        if (id == (*it)->id) { r = *it; break; }
        if (deep) {
            r = (*it)->find(id, deep);
            if (r) break;
        }
    }
    return r;
}
