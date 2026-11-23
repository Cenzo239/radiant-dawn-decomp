#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80079210(void*);
typedef struct SKey { u8 pad[0xe]; u16 xe; } SKey;
typedef struct SVal { SKey* k; u8 x4; } SVal;
typedef struct SN { struct SN* prev; struct SN* next; SVal* val; } SN;
typedef struct SL { unsigned int size; SN* prev; SN* next; } SL;
struct SCmp { char c; };
static inline BOOL sLessK(u16 be, u16 ae, SVal* a, SVal* b) {
    if (ae == be) {
        if (a->x4 != b->x4) return a->x4 < b->x4;
        return b > a;
    }
    return ae < be;
}
static inline BOOL sLess(SVal* a, SVal* b) {
    u16 ae = a->k->xe;
    if (ae == b->k->xe) {
        if (a->x4 != b->x4) return a->x4 < b->x4;
        return b > a;
    }
    return ae < b->k->xe;
}
static inline BOOL sLess1(SVal* a, SVal* b) {
    u16 ae = a->k->xe;
    u16 be = b->k->xe;
    if (ae == be) {
        u8 ax;
        u8 bx;
        bx = b->x4;
        ax = a->x4;
        if (ax != bx) return ax < bx;
        return b > a;
    }
    return ae < be;
}
typedef struct SKey2 { u8 pad[0xe]; u16 xe; } SKey2;
typedef struct SVal2 { SKey2* k; u8 x4; } SVal2;
static inline BOOL sLess2(SVal* const& a, SVal* b) {
    u16 ae = ((SVal2*)a)->k->xe;
    if (ae == ((SVal2*)b)->k->xe) {
        if (((SVal2*)a)->x4 != ((SVal2*)b)->x4) return ((SVal2*)a)->x4 < ((SVal2*)b)->x4;
        return b > a;
    }
    return ae < ((SVal2*)b)->k->xe;
}
static inline void swp(SN*& a, SN*& b) { SN* t = a; a = b; b = t; }
static inline void adv(SN*& it, unsigned int h) { for (unsigned int i = h; i != 0; i--) it = it->next; }
static inline void sSplice2(SN* pos, SN* f, SN* last) {
    pos->prev->next = f;
    f->prev = pos->prev;
    pos->prev = last;
    last->next = pos;
}
static inline void tInit(SL* t) {
    t->size = 0;
    t->next = (SN*)&t->prev;
    t->prev = (SN*)&t->prev;
}
static inline void spl(SL* t, SL* l, SN* it, unsigned int n) {
    if (n != 0) {
        if (t != l) {
            l->size -= n;
            t->size += n;
        }
        SN* last = l->prev;
        it->prev->next = last->next;
        last->next->prev = it->prev;
        t->prev->next = it;
        it->prev = t->prev;
        t->prev = last;
        last->next = (SN*)&t->prev;
    }
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

struct It { SN* n; It(SN* p) : n(p) {} It& operator++() { n = n->next; return *this; } };
static inline void sSplice(SN* pos, SN* f, SN* last) {
    f->prev->next = last->next;
    last->next->prev = f->prev;
    pos->prev->next = f;
    f->prev = pos->prev;
    pos->prev = last;
    last->next = pos;
}
static inline BOOL sLess3(SVal* a, SVal* b, u16& be) {
    u16 ae = ((SVal2*)a)->k->xe;
    be = ((SVal2*)b)->k->xe;
    if (ae == be) {
        if (((SVal2*)a)->x4 != ((SVal2*)b)->x4) return ((SVal2*)a)->x4 < ((SVal2*)b)->x4;
        return b > a;
    }
    return ae < be;
}
#define MERGE(FN) \
void FN(SL* l, SL* x, SCmp c) { \
    if (l != x) { \
        SN* f1 = l->next; \
        SN* f2 = x->next; \
        SN* e1 = (SN*)&l->prev; \
        SN* e2 = (SN*)&x->prev; \
        u16 be; \
        SN* j; \
        SVal* aa; \
        SN* b; \
        SVal* vb; \
        SVal* va; \
        SN* a; \
        unsigned int k; \
        for (; f1 != e1 && f2 != e2; f1 = f1->next) { \
            va = f2->val; \
            vb = f1->val; \
            if (sLess1(va, vb)) { \
                k = 1; \
                j = f2->next; \
                for (; j != e2; j = j->next, k++) { aa = j->val; if (!sLess3(aa, vb, be)) break; } \
                { \
                    SN* last = j->prev; \
                    sSplice(f1, f2, last); \
                    f2 = j; \
                    x->size -= k; \
                    l->size += k; \
                } \
            } \
        } \
        if (f2 != e2 && x->size != 0) { \
            a = x->next; \
            b = x->prev; \
            x->next = (SN*)&x->prev; \
            x->prev = (SN*)&x->prev; \
            sSplice2(f1,a,b); \
            l->size += x->size; \
            x->size = 0; \
        } \
    } \
}
MERGE(fn_801FDE7C)
MERGE(fn_80204738)
MERGE(fn_80210D44)
MERGE(fn_80211154)
}
