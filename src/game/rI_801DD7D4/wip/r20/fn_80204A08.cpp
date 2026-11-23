/* fn_80204A08 (0x4AC), local-vector function, round 20: complete draft, class `other`.
 * Removes from the eight category lists every entry whose owner is `owner`: per list, the matching values
 * are first collected in a local std::vector<void*> (reserve(7), push_back), then each collected value is
 * erased from whichever list holds it (cursor clamped). 8-list sibling of fn_801FEA10 (same instructions; offsets and string pool differ).
 * State: 289 of 299 instructions; blocks, calls and references are right. What differs
 * (tools/equiv/dd.py), all an effect of register pressure (the original uses r14..r31 too):
 *   - ours hoists the addresses of __files, the string pool and lbl_80387C78 out of the loops into saved
 *     registers; the original rematerialises them (`lis/addi`) in each of the five error paths;
 *   - in exchange ours keeps the outer list counter and list pointer in stack slots (frame 0xb0), the
 *     original has them in r14/r22 (frame 0xa0);
 *   - push_back: the original computes `0x3FFFFFFF - cap` twice, ours once;
 *   - ~vector: the original has `size - size` as lwz/subf, ours folds it to 0.
 * Same open point as wip/r18i/fn_8023E264.cpp (fn_8023E264 / fn_8023E8EC), whose vector code this reuses.
 * PVec/SplitBuffer/Buf3 stand in for MSL std::vector<T*> and its __split_buffer; a port should use
 * std::vector. The error paths print to stderr and abort (MSL's length_error/bad_alloc without exceptions). */
#include "game/rI_801DD7D4/types.h"
extern "C" {
extern char lbl_8036FBC0[];     /* this file's string pool; +0x68 = "vector length error" */
extern char lbl_80387C78[];
extern char __files[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
}
struct NList { void* head; void* tail; u16 num; u16 off; };

static inline u32 const& Max(u32 const& a, u32 const& b) { return a < b ? b : a; }
typedef void* T;
struct SplitBuffer {
    T* first;
    u32 size;
    u32 cap;
    void* alloc;
    u32 start;
    SplitBuffer(u32 z, void* a) { first = (T*)z; size = z; cap = z; alloc = a; start = z; }
    ~SplitBuffer() { if (first) { size = 0; fn_80079210(first); } }
};
struct Buf3 {
    T* first;
    u32 size;
    u32 cap;
    Buf3(u32 z) { first = (T*)z; size = z; cap = z; }
    ~Buf3() { if (first) { size = 0; fn_80079210(first); } }
};
static inline void msgOut(const char* m, void* f) {
    fn_80290B48(f, m);
    fn_80291BD0();
}
static inline void lengthError() {
    msgOut(lbl_8036FBC0 + 0x68, __files + 0xa0);
}
struct PVec {
    T* data;
    u32 size;
    u32 cap;
    PVec() { data = 0; size = 0; cap = 0; }
    void shrink(u32 n) { size -= n; }
    ~PVec() { if (data) { shrink(size); fn_80079210(data); } }
    T* begin() { return data; }
    T* end() { return data + size; }
    static u32 dist(T* const& a, T* const& b) { return b - a; }
};
static inline void reserve(PVec* v, u32 n) {
    if (n > v->cap) {
        Buf3 buf(0);
        if (n > 0x3FFFFFFF) {
            lengthError();
        }
        T* mem = (T*)fn_80079150(n * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = n;
        n = PVec::dist(v->begin(), v->end());
        T* old = v->begin();
        memcpy(buf.first + buf.size, old, n * sizeof(T));
        memset(old, 0, n * sizeof(T));
        buf.size += n;
        v->size = 0;
        u32 oc = v->cap;
        v->cap = buf.cap;
        buf.cap = oc;
        T* od = v->data;
        v->data = buf.first;
        buf.first = od;
        v->size = buf.size;
        buf.size = 0;
    }
}
static inline void push_back(PVec* v, T const& x) {
    u32 nc;
    u32 cc;
    u32 s;
    u32 c;
    u32 ns;
    u32 n;
    T* mem;
    u32 cnt;
    T* old;
    u32 oc;
    T* od;
    s = v->size;
    c = v->cap;
    if (s < c) {
        ns = s + 1;
        v->size = ns;
        v->data[ns - 1] = x;
    } else {
        if (0x3FFFFFFF - c < 1) {
            lengthError();
        }
        SplitBuffer buf(0, &v->cap); n = v->size + 1 - c;
        cc = c;
        if (n > 0x3FFFFFFF - cc) {
            lengthError();
        }
        u32 t2; u32 t1;
        if (cc < 0x15555555) {
            t1 = (cc + 1) * 3 / 5;
            nc = cc + Max(t1, n);
        } else if (cc < 0x2AAAAAAA) {
            t2 = (cc + 1) / 2;
            nc = cc + Max(t2, n);
        } else {
            nc = 0x3FFFFFFF;
        }
        if (nc > 0x3FFFFFFF) {
            lengthError();
        }
        mem = (T*)fn_80079150(nc * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = nc;
        buf.start = v->size;
        (buf.first + buf.start)[buf.size] = x;
        buf.size++;
        cnt = PVec::dist(v->begin(), v->end());
        old = v->begin();
        buf.start -= cnt;
        nc = cnt * sizeof(T);
        memcpy(buf.first + buf.start, old, nc);
        memset(old, 0, nc);
        buf.size += cnt;
        v->size = 0;
        oc = v->cap;
        v->cap = buf.cap;
        buf.cap = oc;
        od = v->data;
        v->data = buf.first;
        buf.first = od;
        v->size = buf.size;
        buf.size = 0;
    }
}
/* category list node: value plus the unit that owns the item */
struct LN { LN* prev; LN* next; void* val; void* owner; };
struct RG { u32 size; LN* prev; LN* next; };
struct SS { u8 p[0x68]; s16 cur[8]; u8 p78[0x10]; RG l[8]; };
struct Pr { int pad; void* v; Pr(void* x) { v = x; } };
static inline LN* fnd(LN* b, LN* e, Pr p) { while (b != e && b->val != p.v) b = b->next; return b; }
/* remove the entry holding `it` from whichever of the eight lists has it */
static inline void eraseItem(SS* s, void* it) {
    RG* r = s->l;
    for (int j = 0; j < 8; r++, j++) {
        Pr pr(it);
        LN* f = fnd(r->next, (LN*)&r->prev, pr);
        if (f != (LN*)&r->prev) {
            f->prev->next = f->next;
            f->next->prev = f->prev;
            fn_80079210(f);
            {
            u32 sz = --r->size;
            s16* c = &s->cur[j];
            if (*c >= sz) *c = sz - 1;
            }
            break;
        }
    }
}
#pragma use_lmw_stmw on
extern "C" void fn_80204A08(SS* s, void* owner) {
    for (int c = 0; c < 8; c++) {
        PVec v;
        reserve(&v, 7);
        RG* r = &s->l[c];
        for (LN* n = r->next; n != (LN*)&r->prev; n = n->next) {
            if (n->owner == owner) { T x = n->val; push_back(&v, x); }
        }
        for (T* it = v.begin(), *e = v.end(); it != e; ++it) eraseItem(s, *it);
    }
}
#pragma use_lmw_stmw off
