#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

/* std::list<T*>::sort and merge, one copy per comparison (key byte in the pointed-to struct). */
typedef struct LNode { struct LNode* prev; struct LNode* next; s8* val; } LNode;
typedef struct LList { u32 n; LNode* last; LNode* first; } LList;
struct Cmp { Cmp() {} Cmp(const Cmp& o) : c(o.c) {} char c; };
extern void fn_80079210(void*);
extern void fn_801B3D3C(LList* a, LList* b, Cmp c);
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
void fn_801B3B3C(LList* l, Cmp c) {
    switch (l->n) {
    case 0: case 1: goto done;
    case 2: {
        LNode* a = l->first;
        LNode* b = a->next;
        if (LT1(b->val, a->val)) {
            Sw(a->prev, a->next);
            Sw(b->prev, b->next);
            Sw(l->last, l->first);
        }
        return;
    }
    }
    {
    u32 half;
    LNode* s;
    LNode* m;
    u32 i;
    u32 rest;
    LList t;
    half = l->n >> 1;
    m = l->first;
    for (i = half; i != 0; i--) m = m->next;
    s = End(&t);
    t.n = 0;
    t.first = s;
    t.last = s;
    rest = l->n - half;
    if (rest != 0) {
        if (&t != l) {
            l->n -= rest;
            t.n += rest;
        }
        {
        LNode* e = l->last;
        m->prev->next = e->next;
        e->next->prev = m->prev;
        t.last->next = m;
        m->prev = t.last;
        t.last = e;
        e->next = s;
        }
    }
    fn_801B3B3C(l, c);
    fn_801B3B3C(&t, c);
    fn_801B3D3C(l, &t, c);
    {
    LNode* e;
    LNode* q = t.first;
    e = End(&t);
    if (q != e) {
        LNode* l1 = t.last;
        q->prev->next = l1->next;
        l1->next->prev = q->prev;
        while (q != e) {
            LNode* x = q;
            q = q->next;
            fn_80079210(x);
            t.n--;
        }
    }
    }
    }
done: ;
}

void fn_801B4280(LList* l, Cmp c) {
    switch (l->n) {
    case 0: case 1: goto done;
    case 2: {
        LNode* a = l->first;
        LNode* b = a->next;
        if (LT3(b->val, a->val)) {
            Sw(a->prev, a->next);
            Sw(b->prev, b->next);
            Sw(l->last, l->first);
        }
        return;
    }
    }
    {
    u32 half;
    LNode* s;
    LNode* m;
    u32 i;
    u32 rest;
    LList t;
    half = l->n >> 1;
    m = l->first;
    for (i = half; i != 0; i--) m = m->next;
    s = End(&t);
    t.n = 0;
    t.first = s;
    t.last = s;
    rest = l->n - half;
    if (rest != 0) {
        if (&t != l) {
            l->n -= rest;
            t.n += rest;
        }
        {
        LNode* e = l->last;
        m->prev->next = e->next;
        e->next->prev = m->prev;
        t.last->next = m;
        m->prev = t.last;
        t.last = e;
        e->next = s;
        }
    }
    fn_801B4280(l, c);
    fn_801B4280(&t, c);
    fn_801B4480(l, &t, c);
    {
    LNode* e;
    LNode* q = t.first;
    e = End(&t);
    if (q != e) {
        LNode* l1 = t.last;
        q->prev->next = l1->next;
        l1->next->prev = q->prev;
        while (q != e) {
            LNode* x = q;
            q = q->next;
            fn_80079210(x);
            t.n--;
        }
    }
    }
    }
done: ;
}

void fn_801B3E68(LList* l, Cmp c) {
    switch (l->n) {
    case 0: case 1: goto done;
    case 2: {
        LNode* a = l->first;
        LNode* b = a->next;
        if (LT2((s8*)b->val, (s8*)a->val)) {
            Sw(a->prev, a->next);
            Sw(b->prev, b->next);
            Sw(l->last, l->first);
        }
        return;
    }
    }
    {
    u32 half;
    LNode* s;
    LNode* m;
    u32 i;
    u32 rest;
    LList t;
    half = l->n >> 1;
    m = l->first;
    for (i = half; i != 0; i--) m = m->next;
    s = End(&t);
    t.n = 0;
    t.first = s;
    t.last = s;
    rest = l->n - half;
    if (rest != 0) {
        if (&t != l) {
            l->n -= rest;
            t.n += rest;
        }
        {
        LNode* e = l->last;
        m->prev->next = e->next;
        e->next->prev = m->prev;
        t.last->next = m;
        m->prev = t.last;
        t.last = e;
        e->next = s;
        }
    }
    fn_801B3E68(l, c);
    fn_801B3E68(&t, c);
    fn_801B40B0(l, &t, c);
    {
    LNode* e;
    LNode* q = t.first;
    e = End(&t);
    if (q != e) {
        LNode* l1 = t.last;
        q->prev->next = l1->next;
        l1->next->prev = q->prev;
        while (q != e) {
            LNode* x = q;
            q = q->next;
            fn_80079210(x);
            t.n--;
        }
    }
    }
    }
done: ;
}

}
