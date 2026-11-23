#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80079210(void*);
typedef struct SVal { u8 pad[0x1c]; u8 k; } SVal;
typedef struct SN { struct SN* prev; struct SN* next; SVal* val; } SN;
typedef struct SL { unsigned int size; SN* prev; SN* next; } SL;
struct SCmp { char c; };
static inline void swp(SN*& a, SN*& b) { SN* t = a; a = b; b = t; }
static inline void adv(SN*& it, unsigned int h) {
    for (unsigned int i = h; i != 0; i--) it = it->next;
}
static inline void sClear(SL* t) {
    SN* f = t->next;
    SN* e = (SN*)&t->prev;
    if (f != e) {
        SN* b = t->prev;
        f->prev->next = b->next;
        b->next->prev = f->prev;
        while (f != e) {
            SN* d = f;
            f = f->next;
            fn_80079210(d);
            t->size--;
        }
    }
}
void fn_80224AAC(SL* l, SL* x, SCmp c);
void fn_802248B4(SL* l, SCmp c) {
    switch (l->size) {
    case 0:
    case 1:
        break;
    case 2: {
        SVal* vb; SVal* va;
        SN* a = l->next;
        SN* b = a->next;
        vb = a->val;
        va = b->val;
        if (va->k < vb->k) {
            swp(a->prev, a->next);
            swp(b->prev, b->next);
            swp(l->prev, l->next);
        }
        break;
    }
    default: {
        unsigned int h = l->size >> 1;
        SL t;
        SN* e;
        SN* it = l->next;
        adv(it, h);
        e = (SN*)&t.prev;
        t.size = 0;
        t.next = e;
        t.prev = e;
        {
            unsigned int n = l->size - h;
            if (n != 0) {
                if (&t != l) {
                    l->size -= n;
                    t.size += n;
                }
                SN* last = l->prev;
                it->prev->next = last->next;
                last->next->prev = it->prev;
                t.prev->next = it;
                it->prev = t.prev;
                t.prev = last;
                last->next = e;
            }
        }
        fn_802248B4(l, c);
        fn_802248B4(&t, c);
        fn_80224AAC(l, &t, c);
        sClear(&t);
        break;
    }
    }
}
}
