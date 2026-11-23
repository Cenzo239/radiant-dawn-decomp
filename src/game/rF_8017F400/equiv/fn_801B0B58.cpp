/* fn_801B0B58: like fn_801B09D0 but walking the list backwards with reverse iterators: finds the last entry whose
   key (by sort mode) equals the current one plus d, and returns its distance from the list head minus one.
   The reverse iterator carries a scratch copy for operator* (tmp), as in MSL. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct PE { s8 a0; s8 a1; s8 a2; s8 a3; s8 a4; };
struct Node { Node* prev; Node* next; PE* val; };
struct PList { u32 x0; Node s; };
struct LData { u8 pad[0x18]; PList* list; u8 p2[8]; int x24; };
extern LData* lbl_804CB9BC;
s8 fn_801B0B58(Node** cur, u8 d);
}
struct It {
    Node* p;
    It() {}
    It(Node* n) : p(n) {}
    PE*& operator*() const { return p->val; }
    It& operator++() { p = p->next; return *this; }
    It& operator--() { p = p->prev; return *this; }
};
static inline BOOL operator!=(const It& a, const It& b) { return a.p != b.p; }
struct RI {
    It tmp;
    It cur;
    RI() {}
    RI(It n) : cur(n) {}
    It base() const { return cur; }
    PE* operator*() { tmp = base(); --tmp; return tmp.p->val; }
    RI& operator++() { --cur; return *this; }
};
static inline BOOL operator!=(const RI& a, const RI& b) { return a.base() != b.base(); }
static inline BOOL Eq0(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a2) r = 1; return r; }
static inline BOOL Eq1(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a1) r = 1; return r; }
static inline BOOL Eq2(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a4) r = 1; return r; }
static inline RI Find0(RI first, RI last, s8 k) { while (first != last && !Eq0(*first, k)) ++first; return first; }
static inline RI Find1(RI first, RI last, s8 k) { while (first != last && !Eq1(*first, k)) ++first; return first; }
static inline RI Find2(RI first, RI last, s8 k) { while (first != last && !Eq2(*first, k)) ++first; return first; }
static inline int Dist2(RI first, RI last) { int n = 0; while (first != last) { ++first; n++; } return n; }
static inline int Dist(const RI& first, const RI& last) { return Dist2(first, last); }
s8 fn_801B0B58(Node** cur, u8 d) {
    LData* l = lbl_804CB9BC;
    PList* li = l->list;
    RI r;
    RI rb(&li->s);
    RI re(li->s.next);
    switch (l->x24) {
    case 0:
        r = Find0(rb, re, d = (u8)(d + (*cur)->val->a2));
        break;
    case 1:
        r = Find1(rb, re, d = (u8)(d + (*cur)->val->a1));
        break;
    case 2:
        r = Find2(rb, re, d = (u8)(d + (*cur)->val->a4));
        break;
    }
    return Dist(r, re) - 1;
}
