/* near miss: fn_801B09D0, shape and stack right; 57 words differ in volatile registers only (iterator wants r3, key r6, flag r7). The W r2 = r copy is what keeps the result in its stack slot. fn_801B0B58 is the same with reverse iterators. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct PE { s8 a0; s8 a1; s8 a2; s8 a3; s8 a4; };
struct Node { Node* prev; Node* next; PE* val; };
struct PList { u32 x0; Node s; };
struct LData { u8 pad[0x18]; PList* list; u8 p2[8]; int x24; };
extern LData* lbl_804CB9BC;
struct W { Node* n; };
static inline BOOL Eq0(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a2) r = 1; return r; }
static inline BOOL Eq1(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a1) r = 1; return r; }
static inline BOOL Eq2(PE* e, s8 k) { BOOL r = 0; if (e->a0 >= 0 && k == e->a4) r = 1; return r; }
int fn_801B09D0(Node** cur, u8 d) {
    LData* l = lbl_804CB9BC;
    int k = l->x24;
    PList* li = l->list;
    Node* b = li->s.next;
    Node* e = &li->s;
    W r;
    switch (k) {
    case 0: {
        Node* q = *cur;
        Node* i = b;
        s8 c = d = (u8)(d + q->val->a2);
        while (i != e && !Eq0(i->val, c)) i = i->next;
        r.n = i;
        break; }
    case 1: {
        Node* q = *cur;
        Node* i = b;
        s8 c = d = (u8)(d + q->val->a1);
        while (i != e && !Eq1(i->val, c)) i = i->next;
        r.n = i;
        break; }
    case 2: {
        Node* q = *cur;
        Node* i = b;
        s8 c = d = (u8)(d + q->val->a4);
        while (i != e && !Eq2(i->val, c)) i = i->next;
        r.n = i;
        break; }
    }
    { W r2 = r; Node* q = r2.n; int n = 0; for (; b != q; b = b->next) n++; return n; }
}
}
