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
};
struct Buf3 {
    T* first;
    u32 size;
    u32 cap;
    Buf3(u32 z) { first = (T*)z; size = z; cap = z; }
    ~Buf3() {
        if (first) {
            size = 0;
            fn_80079210(first);
        }
    }
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
        u32 cnt = PVec::dist(v->begin(), v->end());
        T* old = v->begin();
        memcpy(buf.first + buf.size, old, cnt * sizeof(T));
        memset(old, 0, cnt * sizeof(T));
        buf.size += cnt;
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
extern "C" {
#pragma use_lmw_stmw on
void fn_8024CB10(PVec* v, u32 n) { reserve(v, n); }
}
