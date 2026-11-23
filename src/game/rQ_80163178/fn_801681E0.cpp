/* fn_801681E0 and fn_80168558: MSL std::sort over the AI turn-order list (Unit* elements, comparator through a
 * function pointer): __selection_sort (min_element) up to 20 elements, otherwise median-of-three quicksort with a
 * rotating "shuffle" offset (SH) for the median picks. fn_801681E0 takes the comparator by value, fn_80168558 by
 * reference; both are the same template body, written once as a macro. Names guessed. Round m15. */
#include "game/rQ_80163178/base.h"
#pragma use_lmw_stmw on
#pragma auto_inline off

typedef int (*CmpF)(u32, u32);
struct Cmp { CmpF f; };

extern "C" {
extern int lbl_804CA7B4;
extern int lbl_804CA7B8;
void fn_801688D0(u32* a, u32* b, u32* c, Cmp* f);
void fn_80168558(u32* first, u32* last, Cmp* comp);
}

#define SWAP(a, b) { u32 t = *(a); *(a) = *(b); *(b) = t; }

static inline u32* MinE(u32* f, u32* l, Cmp* c) {
    u32* k;
    u32* r = f;
    if (f != l) {
        for (k = f + 1; k != l; ++k) {
            if (c->f(*k, *r)) r = k;
        }
    }
    return r;
}
static inline void Sel(u32* first, u32* last, Cmp* c) {
    if (first == last) return;
    u32* j = last;
    --j;
    while (first != j) {
        u32* i = MinE(first, last, c);
        if (i != first) SWAP(i, first)
        ++first;
    }
}
#define SORT_BODY(C, SH) \
    for (;;) { \
        len = last - first; \
        if (len <= 1) return; \
        if (len <= 20) { \
            Sel(first, last, C); \
            return; \
        } \
        m1 = first + (len / 4 + SH % 5); \
        if (++SH >= 5) SH = -4; \
        { q = 3 * len / 4; m2 = first + (q + SH % 5); } \
        if (++SH >= 5) SH = -4; \
        pivot = last - 1; \
        fn_801688D0(m1, m2, pivot, C); \
        i = first; \
        j = pivot; \
        while ((C)->f(*i, *pivot)) ++i; \
        for (;;) { \
            --j; \
            if (i == j || (C)->f(*j, *pivot)) break; \
        } \
        if (i < j) { \
            SWAP(i, j) \
            ++i; \
            for (;;) { \
                while ((C)->f(*i, *pivot)) ++i; \
                while (!(C)->f(*--j, *pivot)) {} \
                if (i >= j) break; \
                SWAP(i, j) \
                ++i; \
            } \
        } \
        if (i == first) { \
            SWAP(i, pivot) \
            ++i; \
            j = last; \
            if (!(C)->f(*first, *--j)) { \
                while (i != last && !(C)->f(*first, *i)) ++i; \
                if (i < j) SWAP(i, j) \
            } \
            if (i < j) { \
                for (;;) { \
                    while (!(C)->f(*first, *i)) ++i; \
                    while ((C)->f(*first, *--j)) {} \
                    if (i >= j) break; \
                    SWAP(i, j) \
                    ++i; \
                } \
            } \
            first = i; \
        } else if (i - first < last - i) { \
            fn_80168558(first, i, C); \
            first = i; \
        } else { \
            fn_80168558(i, last, C); \
            last = i; \
        } \
    }

extern "C" {
void fn_801681E0(u32* first, u32* last, CmpF comp) {
    u32* k;
    u32* j;
    u32* pivot;
    u32* m1;
    u32* m2;
    int len;
    u32* i;
    u32* min;
    u32* end;
    int q;
    SORT_BODY((Cmp*)&comp, lbl_804CA7B4)
}
void fn_80168558(u32* first, u32* last, Cmp* comp) {
    u32* j;
    u32* min;
    u32* k;
    u32* pivot;
    u32* i;
    int q;
    u32* m2;
    u32* m1;
    u32* end;
    int len;
    SORT_BODY(comp, lbl_804CA7B8)
}
}
