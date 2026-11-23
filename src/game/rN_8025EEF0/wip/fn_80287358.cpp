/* NEAR MISS (round 17): 93 positional lines, registers only. The pooled "vector length error" literal fixed the string base rank; left: reserve mem/old, loop i/seen/c ranks, tbl loop volatiles, sort loop j. */
/* Unit record: pick the unit to show first (sorted vector of units) */
#include "game/rN_8025EEF0/types.h"

extern "C" {
extern char __files[];
extern char lbl_80387C78[];
extern char lbl_80373C40[];
extern int lbl_804CAB50;
extern u8* lbl_804CB810;
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
}

static inline u32 const& Max(u32 const& a, u32 const& b) {
    return a < b ? b : a;
}

typedef u8* T;
struct SplitBuffer {
    T* first;
    u32 size;
    u32 cap;
    void* alloc;
    u32 start;

    SplitBuffer(u32 z, void* a) {
        first = (T*)z;
        size = z;
        cap = z;
        alloc = a;
        start = z;
    }
    ~SplitBuffer() {
        if (first) {
            size = 0;
            fn_80079210(first);
        }
    }
};

#pragma pool_strings on
static inline void msgOut(const char* m, void* f) {
    fn_80290B48(f, m);
    fn_80291BD0();
}
static inline void msgOut2(void* f, const char* m) { fn_80290B48(f, m); fn_80291BD0(); }
static inline void msgOut3(const char* const& m, void* f) { fn_80290B48(f, m); fn_80291BD0(); }
static inline void lengthError() {
    msgOut("vector length error", __files + 0xa0);
}

struct PVec {
    T* data;
    u32 size;
    u32 cap;

    inline void push_back(T const& x);
    T* begin() { return data; }
    T* end() { return data + size; }
    static u32 dist(T* const& a, T* const& b) { return b - a; }
};

struct TmpVec {
    T* data;
    u32 size;
    u32 cap;
    TmpVec() { data = 0; size = 0; cap = 0; }
    ~TmpVec() {
        if (data) {
            size = 0;
            fn_80079210(data);
        }
    }
};

static inline void reserve(PVec* v, u32 n) {
    if (v->cap < n) {
/*P*/
        T* mem;
        u32 cnt;
        T* old;
        u32 oc;
        T* od;
        u32 os;
/*E*/
        TmpVec t;
        mem = (T*)fn_80079150(n * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        t.data = mem;
        t.cap = n;
        cnt = PVec::dist(v->begin(), v->end());
        old = v->begin();
        memcpy(t.data + t.size, old, cnt * sizeof(T));
        memset(old, 0, cnt * sizeof(T));
        t.size += cnt;
        v->size = 0;
        oc = v->cap; v->cap = t.cap; t.cap = oc;
        od = v->data; v->data = t.data; t.data = od;
        os = v->size; v->size = t.size; t.size = os;
    }
}

static inline u32 maxs() { return 0x3FFFFFFF; }
static inline void chk(u32 n, u32 c) { if (n > 0x3FFFFFFF - c) lengthError(); }
static inline void chk2(u32 const& n, u32 const& c) { if (0x3FFFFFFF - c < n) lengthError(); }
static inline void chk3(u32 const& n, u32 const& c) { if (n > 0x3FFFFFFF - c) lengthError(); }
static inline void chk4(u32 n, u32 const& c) { if (n > 0x3FFFFFFF - c) lengthError(); }
static inline void push_back(PVec* v, T const& x) {
/*P*/
    T* mem;
    u32 c;
    u32 ns;
    u32 n;
    u32 s;
    u32 cnt;
    T* old;
    u32 oc;
    T* od;
/*E*/
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
        chk3(n, c);
        u32 t2; u32 t1;
        if (c < 0x15555555) {
            t1 = (c + 1) * 3 / 5;
            c += Max(t1, n);
        } else if (c < 0x2AAAAAAA) {
            t2 = (c + 1) / 2;
            c += Max(t2, n);
        } else {
            c = 0x3FFFFFFF;
        }
        if (c > 0x3FFFFFFF) {
            lengthError();
        }
        mem = (T*)fn_80079150(c * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = c;
        buf.start = v->size;
        (buf.first + buf.start)[buf.size] = x;
        buf.size++;
        cnt = PVec::dist(v->begin(), v->end());
        old = v->begin();
        buf.start -= cnt;
        memcpy(buf.first + buf.start, old, cnt * sizeof(T));
        memset(old, 0, cnt * sizeof(T));
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

inline void PVec::push_back(T const& x) { ::push_back(this, x); }
static inline void vclear(PVec* v) { int n = ((u8*)v->data + v->size) - (u8*)v->data; v->size -= n; }

struct UVec : PVec {
    UVec() { data = 0; size = 0; cap = 0; }
    ~UVec() {
        vclear(this);
        if (data) {
            vclear(this);
            fn_80079210(data);
        }
    }
};

static inline void swp(T& a, T& b) { T t = a; a = b; b = t; }
static inline T& at(PVec* v, const int& i) { return v->data[i]; }
static inline u8* unitAt(u8 id) { return id ? lbl_804CB810 + (id - 1) * 0x3F0 : 0; }

extern "C" {
#pragma use_lmw_stmw on
u8* fn_80287358(void) {
/*P*/
    const u8* p;
    int i;
    u8* u;
    int n;
    int last;
    int i2;
    int j;
    u8* a;
    int k;
    u8* b;
/*E*/
    UVec v;
    reserve(&v, 0x50);
    const u8 tbl[7] = {0x00, 0x05, 0x07, 0x08, 0x09, 0x0A, 0xFF};
    u8 seen[0xB];
    memset(seen, (u8)lbl_804CAB50, 0xB);
    for (p = tbl; *p != 0xFF; p++) seen[*p] = 1;
    for (i = 1; i <= 0xFE; i++) {
        u = unitAt(i);
        if (*(void**)(u + 0xEC) != 0 && seen[(*(u8**)(u + 0xF4))[8]] != 0) v.push_back(u);
    }
    n = (u8)v.size;
    last = n - 1;
    for (i2 = 0; i2 < n; i2++) {
        for (j = 0; j < last - i2; j++) {
            a = at(&v, j);
            k = j + 1;
            b = at(&v, k);
            if (*(u16*)(a + 0x384) >= *(u16*)(b + 0x384)) {
                if (*(u16*)(a + 0x384) != *(u16*)(b + 0x384) || *(u16*)(*(u8**)(a + 0xEC) + 0x1C) <= *(u16*)(*(u8**)(b + 0xEC) + 0x1C)) {
                    swp(at(&v, j), at(&v, k));
                }
            }
        }
    }
    return *(u8**)(at(&v, last) + 0xEC);
}
#pragma use_lmw_stmw off
}
