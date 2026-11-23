/* Text-run list setup: merges runs of equal attribute into a vector of 8-byte items */
#include "game/rN_8025EEF0/calls.h"

extern "C" {
extern char __files[];
extern char lbl_8037387C[];
extern char lbl_80392A48[];
extern void* lbl_803929B0[][2];
extern u8 lbl_803CAB38[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* fn_8001D3B4(void* p);
int fn_8006041C(void* p);
void fn_80060528(void* p, int i, u8* a, u16* b, u32* c);
u8* fn_8024BCA0(void);
}
inline void* operator new(unsigned long, void* p) { return p; }

#pragma pool_strings on
/* The original strings of this file's pool (lbl_8037387C), in order. */
void StringPool(const char** p) {
    p[0] = "9999";
    p[1] = "%d";
    p[2] = "99:99:99";
    p[3] = "%02d:%02d:%02d";
}

struct W2 { u32 a, b; };
struct W2a { u32 w[2]; };
struct E {
    u8 a;
    u16 b;
    u32 c;
    E() {}
    E(u8 x, u16 y, u32 z) : a(x), b(y), c(z) {}
    E(const E& o) { *(W2a*)this = *(const W2a*)&o; }
};
static inline u32 const& Max(u32 const& a, u32 const& b) { return a < b ? b : a; }
typedef E T;
struct SplitBuffer {
    T* first;
    u32 size;
    u32 cap;
    void* alloc;
    u32 start;
    SplitBuffer(u32 z, void* a) { first = (T*)z; size = z; cap = z; alloc = a; start = z; }
    ~SplitBuffer() { if (first) { size = 0; fn_80079210(first); } }
};
static inline void msgOut(const char* m, void* f) {
    fn_80290B48(f, m);
    fn_80291BD0();
}
static inline void msgOut2(void* f, const char* m) { fn_80290B48(f, m); fn_80291BD0(); }
static inline void lengthError() {
    msgOut("vector length error", __files + 0xA0);
}
struct PVec {
    T* data;
    u32 size;
    u32 cap;
    T* begin() { return data; }
    T* end() { return data + size; }
};
static inline void push_back(PVec* v, T const& x) {
/*Q*/
    u32 t1;
    u32 t2;
    u32 s;
    u32 c;
    u32 ns;
    u32 n;
    T* mem;
    u32 cc;
    u32 oc;
    T* od;
    T* b;
    T* e;
    T* d;
/*EQ*/
    s = v->size;
    c = v->cap;
    if (s < c) {
        ns = s + 1;
        v->size = ns;
        v->data[ns - 1] = x;
    } else {
        if (0x1FFFFFFF - c < 1) {
            lengthError();
        }
        SplitBuffer buf(0, &v->cap); n = v->size + 1 - v->cap;
        cc = v->cap;
        if (n > 0x1FFFFFFF - cc) {
            lengthError();
        }
        if (cc < 0xAAAAAAA) {
            t1 = (cc + 1) * 3 / 5;
            cc = cc + Max(t1, n);
        } else if (cc < 0x15555554) {
            t2 = (cc + 1) / 2;
            cc = cc + Max(t2, n);
        } else {
            cc = 0x1FFFFFFF;
        }
        if (cc > 0x1FFFFFFF) {
            lengthError();
        }
        mem = (T*)fn_80079150(cc * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80392A48);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = cc;
        buf.start = v->size;
        (buf.first + buf.start)[buf.size] = x;
        d = buf.first + buf.start;
        buf.size++;
        b = v->begin();
        e = v->end();
        while (e > b) {
            --e;
            --d;
            new (d) T(*e);
            buf.start--;
            buf.size++;
        }
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

struct RunObj {
    u8 pad0[0x30];
    u8 x30; u8 x31; u8 pad32[2];
    void* x34;
    u8 pad38[4];
    s16 x3C; s16 x3E; s16 x40; u8 x42; u8 x43; s16 x44; u8 x46; u8 x47;
    s16 x48; u8 pad4A[2];
    PVec v;
};

extern "C" {
#pragma use_lmw_stmw on
void fn_8027F368(RunObj* o) {
/*P*/
    u8 cur;
    u32 sc;
    u16 sb;
    u8* src;
    u16 n;
    int k;
    s8 lang;
    int z;
/*E*/
    E e;
    z = 0;
    o->x30 = z;
    o->x46 = z;
    o->x3C = z;
    o->x3E = 0x1A8;
    o->x40 = 0x1E;
    o->x42 = z;
    o->x43 = 1;
    o->x44 = 0x1E;
    o->x47 = z;
    lang = fn_8024BC94()[0x1BC8];
    o->x34 = fn_8001D3B4(lbl_803929B0[lang][fn_801D09F0()]);
    o->x48 = z;
    src = lbl_803CAB38 + 0x554;
    cur = 0xFF;
    sc = 0;
    sb = 0;
    e.a = cur;
    e.c = z;
    e.b = z;
    n = (u16)fn_8006041C(src);
    for (k = 0; k <= n; k++) {
        fn_80060528(src, k, &e.a, &e.b, &e.c);
        if (cur == e.a) {
            sb += e.b;
            sc += e.c;
            continue;
        }
        if (cur != 0xFF) push_back(&o->v, E(cur, sb, sc));
        cur = e.a;
        sb = e.b;
        sc = e.c;
    }
    o->x48 = o->v.size;
    if (fn_8024BCA0()[0x34] >= 2) o->x31 = 1; else o->x31 = 0;
}
#pragma use_lmw_stmw off
}
