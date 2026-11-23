/* r20: `regs` (check_regs.py). Copy of wip/fn_801B3D3C_ends.cpp (two volatile registers swapped). */
/* near miss: fn_801B3D3C, 9 words: e2 wants r11 and j r8, otherwise right. The tail must recompute End(b), which removes the size miss. fn_801B4480 and fn_801B40B0 should follow. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

/* std::list<T*>::sort and merge, one copy per comparison (key byte in the pointed-to struct). */
typedef struct LNode { struct LNode* prev; struct LNode* next; s8* val; } LNode;
typedef struct LList { u32 n; LNode* last; LNode* first; } LList;
struct Cmp { Cmp() {} Cmp(const Cmp& o) : c(o.c) {} char c; };
extern void fn_80079210(void*);

extern void fn_801B3B3C(LList* l, Cmp c);
extern void fn_801B3E68(LList* l, Cmp c);
extern void fn_801B40B0(LList* a, LList* b, Cmp c);
extern void fn_801B4280(LList* l, Cmp c);
extern void fn_801B4480(LList* a, LList* b, Cmp c);

static inline void Sw(LNode*& x, LNode*& y) { LNode* t = x; x = y; y = t; }
static inline LNode* End(LList* l) { return (LNode*)&l->last; }

#define KEYA(p) ((p)[0])
#define LT1(a, b) (KEYA(a) < KEYA(b))
#define LT3(a, b) ((a)[3] < (b)[3])
static inline BOOL LT2(s8* a, s8* b) { if (a[1] == b[1]) return a[3] < b[3]; return a[1] < b[1]; }
void fn_801B3D3C(LList* a, LList* b, Cmp c) {
/*P*/
    LNode* e1;
    LNode* e2;
    LNode* t;
    LNode* f2;
    LNode* j;
    int k;
    LNode* l2;
    LNode* h;
    LNode* f1;
    s8 key;
    s8* v;
/*E*/
    if (a == b) return;
    f1 = a->first;
    e1 = End(a);
    f2 = b->first;
    e2 = End(b);
    for (; f1 != e1 && f2 != e2; f1 = f1->next) {
        v = f1->val;
        key = v[0];
        if (f2->val[0] < key) {
            j = f2->next;
            k = 1;
            for (; j != e2; j = j->next) {
                if (!(j->val[0] < key)) break;
                k++;
            }
            {
            l2 = j->prev;
            f2->prev->next = l2->next;
            l2->next->prev = f2->prev;
            f1->prev->next = f2;
            f2->prev = f1->prev;
            f2 = j;
            f1->prev = l2;
            l2->next = f1;
            }
            b->n -= k;
            a->n += k;
        }
    }
    if (f2 != e2 && b->n != 0) {
        h = b->first;
        t = b->last;
        b->first = End(b);
        b->last = End(b);
        f1->prev->next = h;
        h->prev = f1->prev;
        f1->prev = t;
        t->next = f1;
        a->n += b->n;
        b->n = 0;
    }
}
}
