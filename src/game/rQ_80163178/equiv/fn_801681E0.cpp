/* fn_801681E0 and fn_80168558: functionally equal (regs level per tools/check_regs.py; registers differ from the original). */
/* symcheck: (b) fn_801681E0 and fn_80168558, block 26: `if (i == j) break;` compiles to cmplw j,i where the original has cmplw i,j; only beq tests it and the flags die there (clean with --eqsym). Writing `j == i` changes nothing. */
/* MSL-style std::sort over the AI turn-order list (Unit* elements, comparator through a function
 * pointer): selection sort up to 20 elements, otherwise median-of-three quicksort with a rotating
 * "shuffle" offset (SH) for the median picks. fn_801681E0 takes the comparator by value,
 * fn_80168558 by reference; both are the same template body, written once as a macro. Names guessed. */
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

#define SORT_BODY(C, SH) \
    for (;;) { \
        u32* i; \
        u32* j; \
        u32* pivot; \
        u32* m1; \
        u32* m2; \
        int len = last - first; \
        if (len <= 1) return; \
        if (len <= 20) { \
            u32* end; \
            if (first == last) return; \
            end = last - 1; \
            for (; first != end; ++first) { \
                u32* min = first; \
                if (first != last) { \
                    u32* k; \
                    for (k = first + 1; k != last; ++k) { \
                        if ((C)->f(*k, *min)) min = k; \
                    } \
                } \
                if (min != first) SWAP(min, first) \
            } \
            return; \
        } \
        m1 = first + (len / 4 + SH % 5); \
        if (++SH >= 5) SH = -4; \
        { int q = 3 * len / 4; m2 = first + (q + SH % 5); } \
        if (++SH >= 5) SH = -4; \
        pivot = last - 1; \
        fn_801688D0(m1, m2, pivot, C); \
        i = first; \
        j = pivot; \
        while ((C)->f(*i, *pivot)) ++i; \
        do { \
            --j; \
            if (i == j) break; \
        } while (!(C)->f(*j, *pivot)); \
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
    SORT_BODY((Cmp*)&comp, lbl_804CA7B4)
}
void fn_80168558(u32* first, u32* last, Cmp* comp) {
    SORT_BODY(comp, lbl_804CA7B8)
}
}
