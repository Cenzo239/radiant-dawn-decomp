/* NEAR MISS (round 17): 225 positional lines, registers only (shape matches). u64 members give the element copy order and keep e scalar; the parameter wants r18 below the hoisted constants, save r31. */
/* Unit record list: build the slot vector from the save's records, padded to four */
#include "game/rN_8025EEF0/calls.h"

extern "C" {
extern char __files[];
extern char lbl_80392B64[];
extern void* lbl_80392AE0[][2];
extern char lbl_804CA798[];
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* fn_8001D3B4(void* p);
void* fn_80177284(void (*f)(void*), void* p);
void fn_802818FC(void* p);
u8 fn_802457BC(void* s);
struct E24;
E24* fn_80245878(void* s, int i);
void* fn_80078CCC(int size, const char* name, int a);
void* fn_80179660(void* p);
void fn_8017985C(void* p, int a);
void fn_80179864(void* p, int a);
void fn_801798A8(void* p, int a);
void fn_80179A7C(void* p, int a);
void fn_8017980C(void* p, int a, int b, int c);
}
inline void* operator new(unsigned long, void* p) { return p; }

#pragma pool_strings on

struct W2 { u32 a, b; };
struct E24 {
    u64 p0;
    u8 b8;
    u8 b9;
    s16 hA;
    u32 wC;
    u64 p10;
    E24() {}
    E24(const E24& o) : p0(o.p0), b8(o.b8), b9(o.b9), hA(o.hA), wC(o.wC), p10(o.p10) {}
};
typedef E24 E;
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
        if (0x0AAAAAAA - c < 1) {
            lengthError();
        }
        SplitBuffer buf(0, &v->cap); n = v->size + 1 - v->cap;
        cc = v->cap;
        if (n > 0x0AAAAAAA - cc) {
            lengthError();
        }
        if (cc < 0x38E38E3) {
            t1 = (cc + 1) * 3 / 5;
            cc = cc + Max(t1, n);
        } else if (cc < 0x71C71C6) {
            t2 = (cc + 1) / 2;
            cc = cc + Max(t2, n);
        } else {
            cc = 0x0AAAAAAA;
        }
        if (cc > 0x0AAAAAAA) {
            lengthError();
        }
        mem = (T*)fn_80079150(cc * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80392B64);
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


struct Rec {
    u8 pad0[0x30];
    void* x30;
    void* x34;
    u8 pad38[0x15];
    u8 x4D;
    u8 pad4E[2];
    void* x50;
    PVec v;
};

static inline void addSaved(Rec* o) {
    void* save = fn_8024BC94();
    o->x4D = fn_802457BC(save);
    for (int i = o->x4D - 1; i >= 0; i--) {
        push_back(&o->v, *fn_80245878(save, i));
    }
}
static inline void pad4(Rec* o) {
    if (o->x4D < 4) {
        for (int j = o->x4D; j < 4; j++) {
            E e;
            e.b8 = 0xFF;
            push_back(&o->v, e);
        }
        o->x4D = 4;
    }
}
extern "C" {
#pragma use_lmw_stmw on
void fn_802811E8(Rec* o) {
/*P*/
    s8 lang;
    void* save;
    int i;
    int j;
    void* p;
/*E*/
    lang = fn_8024BC94()[0x1BC8];
    o->x30 = fn_8001D3B4(lbl_80392AE0[lang][fn_801D09F0()]);
    o->x34 = fn_80177284(fn_802818FC, o);
    addSaved(o);
    pad4(o);
    p = fn_80078CCC(0x2C, lbl_804CA798, 0);
    if (p != 0) p = fn_80179660(p);
    o->x50 = p;
    fn_8017985C(o->x50, o->x4D);
    fn_80179864(o->x50, 4);
    fn_801798A8(o->x50, 1);
    fn_80179A7C(o->x50, 0xFF);
    fn_8017980C(o->x50, 0x235, 0x67, 0x124);
}
#pragma use_lmw_stmw off
}
