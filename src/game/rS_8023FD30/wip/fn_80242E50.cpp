#include "game/rS_8023FD30/types.h"

extern "C" {
extern char __files[];
extern char lbl_80387C78[];
extern char lbl_80372B4C[];
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

typedef void* T;
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
extern "C" void rS_pool0(const char*);
void rS_poolDummy() {
    rS_pool0("CP_ATKSEQ_LIST");
    rS_pool0("CP_MOVSEQ_LIST");
    rS_pool0("CP_HEALSEQ_LIST");
    rS_pool0("CP_MTYPE_LIST");
}
static inline void msgOut(const char* m, void* f) {
    fn_80290B48(f, m);
    fn_80291BD0();
}
static inline void lengthError() {
    msgOut("vector length error", __files + 0xa0);
}

struct PVec {
    T* data;
    u32 size;
    u32 cap;

    T* begin() { return data; }
    T* end() { return data + size; }
    static u32 dist(T* const& a, T* const& b) { return b - a; }
    u32 getCap() { return cap; }
    u32 getSize() { return size; }
};

static inline u32 grow(PVec* v, u32 n0) {
/*Q*/
    u32 n;
    u32 t2;
    u32 c;
    u32 t1;
/*E2*/
    n = n0;
    c = v->cap;
    if (n > 0x3FFFFFFF - c) {
        lengthError();
    }
    if (c < 0x15555555) {
        t1 = (c + 1) * 3 / 5;
        return c + Max(t1, n);
    }
    if (c < 0x2AAAAAAA) {
        t2 = (c + 1) / 2;
        return c + Max(t2, n);
    }
    return 0x3FFFFFFF;
}
static inline void push_back(PVec* v, T const& x) {
/*P*/
    u32 nc;
    u32 cc;
    u32 s;
    u32 c;
    u32 ns;
    u32 sz;
    u32 cp;
    u32* pc;
    u32 n;
    u32 z;
    T* mem;
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
        sz = v->size; cp = v->cap; n = sz + 1 - cp;
        pc = &v->cap;
        z = 0;
        SplitBuffer buf(z, pc);
        cc = v->cap;
        if (n > 0x3FFFFFFF - cc) {
            lengthError();
        }
        if (cc < 0x15555555) {
            u32 t1 = (cc + 1) * 3 / 5;
            nc = cc + Max(t1, n);
        } else if (cc < 0x2AAAAAAA) {
            u32 t2 = (cc + 1) / 2;
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

extern "C" {
#pragma use_lmw_stmw on
void fn_80242E50(PVec* v, T const& x) {
    push_back(v, x);
}
}
/* WIP: vector<T*>::push_back, family of 8 at 0x2C4 (each a member at a different offset, so a macro
   over the offset once this matches) plus the reserve fn_8024CB10. Head and cc/nc registers now fit
   with named locals. Left: in the slow path size/cap/&cap/zero want r4/r5/r6/r7 with n in r4; the
   zero and &cap temporaries get coloured first here. The t1 and t2 slots also need swapping. */
