/* fn_80056338 / fn_80056B70 / fn_800573A8 (round 16): quicksort of the 0x24-byte entries of the
 * lbl_803E7320 list by the key at +4 (two instantiations of one sort template, each with its own
 * pivot-jitter counter, plus the median-of-three helper). Selection sort below 21 entries. */
typedef signed char s8;
typedef unsigned char u8;
struct UP { s8 x; s8 y; u8 c; u8 d; int k[4]; int e, f, g, h; };
struct Sort1 {
    u8 b;
    bool operator()(const UP& a, const UP& b) const { return a.k[0] < b.k[0]; }
};
extern "C" {
extern int lbl_804CA340;
extern int lbl_804CA344;
void fn_80056B70(UP* first, UP* last, Sort1& comp);
void fn_800573A8(UP* a, UP* b, UP* c, Sort1& comp);
}
#pragma use_lmw_stmw on
#pragma inline_max_size(4000)
#pragma inline_max_total_size(20000)
static inline void swp(UP& a, UP& b) {
    UP t = a;
    a = b;
    b = t;
}
static inline UP* pick(UP* first, int q, int& s) {
    UP* r = first + (q + s % 5);
    if (++s >= 5) {
        s = -4;
    }
    return r;
}
static inline UP* minElem(UP* first, UP* last, Sort1& comp) {
    UP* r = first;
    if (first != last) {
        for (UP* p = first + 1; p != last; ++p) {
            if (comp(*p, *r)) {
                r = p;
            }
        }
    }
    return r;
}
#define SORT_BODY(S) \
    UP* i; \
    int n; \
    UP* m1; \
    UP* m2; \
    UP* piv; \
    Sort1* cp = &comp; \
    UP* j; \
    UP* m; \
    for (;;) { \
        n = last - first; \
        if (n <= 1) { \
            goto end; \
        } \
        if (n <= 20) { \
            if (first == last) { \
                goto end; \
            } \
            for (; first != last - 1; ++first) { \
                m = minElem(first, last, *cp); \
                if (m != first) { \
                    swp(*m, *first); \
                } \
            } \
            goto end; \
        } \
        m1 = pick(first, n / 4, S); \
        m2 = pick(first, n * 3 / 4, S); \
        piv = last - 1; \
        fn_800573A8(m1, m2, piv, *cp); \
        i = first; \
        j = piv; \
        while ((*cp)(*i, *piv)) { \
            ++i; \
        } \
        while (i != --j && !(*cp)(*j, *piv)) { \
        } \
        if (i < j) { \
            swp(*i, *j); \
            ++i; \
            for (;;) { \
                while ((*cp)(*i, *piv)) { \
                    ++i; \
                } \
                while (!(*cp)(*--j, *piv)) { \
                } \
                if (i >= j) { \
                    break; \
                } \
                swp(*i, *j); \
                ++i; \
            } \
        } \
        if (i == first) { \
            swp(*i, *piv); \
            ++i; \
            j = last - 1; \
            if (!(*cp)(*first, *(last - 1))) { \
                while (i != last && !(*cp)(*first, *i)) { \
                    ++i; \
                } \
                if (i < j) { \
                    swp(*i, *j); \
                } \
            } \
            if (i < j) { \
                for (;;) { \
                    while (!(*cp)(*first, *i)) { \
                        ++i; \
                    } \
                    while ((*cp)(*first, *--j)) { \
                    } \
                    if (i >= j) { \
                        break; \
                    } \
                    swp(*i, *j); \
                    ++i; \
                } \
            } \
            first = i; \
            continue; \
        } \
        if (i - first < last - i) { \
            fn_80056B70(first, i, *cp); \
            first = i; \
        } else { \
            fn_80056B70(i, last, *cp); \
            last = i; \
        } \
    } \
end:;

extern "C" void fn_80056338(UP* first, UP* last, Sort1 comp) {
    SORT_BODY(lbl_804CA340)
}
#pragma push
#pragma auto_inline off
extern "C" void fn_80056B70(UP* first, UP* last, Sort1& comp) {
    SORT_BODY(lbl_804CA344)
}
#pragma pop
extern "C" void fn_800573A8(UP* a, UP* b, UP* c, Sort1& comp) {
    bool x = !comp(*c, *a);
    bool y = !comp(*b, *c);
    if (x && y) {
        return;
    }
    if (!x && !y) {
        swp(*a, *b);
        return;
    }
    if (comp(*b, *a)) {
        swp(*a, *b);
    }
    if (x) {
        swp(*b, *c);
    } else {
        swp(*a, *c);
    }
}
