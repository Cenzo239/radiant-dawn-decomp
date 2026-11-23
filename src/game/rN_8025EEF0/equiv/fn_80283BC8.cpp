/* functionally equal (check_regs: regs). Unit record list: collect the army's units of the listed affiliations into a vector of {unit, object} pairs,
   bubble-sort them, set up the first entry's object and the last five portraits. Round 18, written from the asm;
   the vector code is the push_back of fn_8027F368.cpp with a pointer-pair element. */
#include "game/rN_8025EEF0/calls.h"

extern "C" {
extern char __files[];
extern char lbl_80392D00[];
extern void* lbl_80392C58[][2];
extern int lbl_804CAB50;
extern u8* lbl_804CB810;
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* fn_8001D3B4(void* p);
u8* fn_8024BCA0(void);
void* memset(void*, int, u32);
u32* fn_80006E1C(void);
void* fn_800F4544(u8* u, const char* s);
void* fn_8000BD3C(void* res);
void fn_80006F20(u32* p);
void* fn_801246A4(u8* u);
u8* fn_800C6210(void* p, int a);
}
inline void* operator new(unsigned long, void* p) { return p; }

#pragma pool_strings on
struct W2a { u32 w[2]; };
struct E {
    u8* u;
    u32* p;
    E() {}
    E(u8* x, u32* y) : u(x), p(y) {}
    E(const E& o) { u = o.u; p = o.p; }
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
static inline void push_back(PVec* v, u8* xu, u32* xp) {
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
        { T* d0 = &v->data[ns - 1]; d0->u = xu; d0->p = xp; }
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
            fn_80290B48(__files + 0xa0, lbl_80392D00);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = cc;
        buf.start = v->size;
        { T* d1 = &(buf.first + buf.start)[buf.size]; d1->u = xu; d1->p = xp; }
        d = buf.first + buf.start;
        buf.size++;
        b = v->begin();
        e = v->end();
        while (e > b) {
            --e;
            --d;
            if (d) *(W2a*)d = *(const W2a*)e;
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


struct RecObj {
    u8 pad0[0x34];
    u8 x34;
    u8 pad35[3];
    void* x38;
    u8 pad3C[0x30];
    PVec v;         /* 0x6C */
    u8 x78;
    u8 pad79[3];
    u8* x7C[5];
};
static inline u8* unitAt(u8 id) { return id ? lbl_804CB810 + (id - 1) * 0x3F0 : 0; }
#define TY(u) ((*(u8**)((u) + 0xF4))[8])
#define LV(u) (*(u8*)((u) + 0x38E))
#define EX(u) (*(u16*)((u) + 0x384))
#define ID(u) (*(u16*)(*(u8**)((u) + 0xEC) + 0x1C))

extern "C" {
#pragma use_lmw_stmw on
void fn_80283BC8(RecObj* o) {
    const u8* p;
    int i;
    int j;
    s8 lang;
    lang = fn_8024BC94()[0x1BC8];
    o->x38 = fn_8001D3B4(lbl_80392C58[lang][fn_801D09F0()]);
    const u8 tbl[8] = {0x00, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF};
    u8 seen[0xB];
    memset(seen, (u8)lbl_804CAB50, 0xB);
    for (p = tbl; *p != 0xFF; p++) seen[*p] = 1;
    for (i = 1; i <= 0xFE; i++) {
        u8* u = unitAt(i);
        if (*(void**)(u + 0xEC) != 0 && seen[TY(u)] != 0) push_back(&o->v, u, 0);
    }
    o->x78 = o->v.size;
    for (i = 0; i < o->x78; i++) {
        int jo;     /* byte offset of element j, stepped after j as in the original */
        for (j = 0, jo = 0; j < o->x78 - 1 - i; j++, jo += 8) {
            int k = j + 1;
            u8* a = ((E*)((u8*)o->v.data + jo))->u;
            u8* b = o->v.data[k].u;
            if (TY(a) == 6 && TY(b) != 6) continue;
            if (TY(a) == 6 && TY(b) == 6 && LV(a) < LV(b)) continue;
            if (TY(a) == 6 && TY(b) == 6 && LV(a) == LV(b) && EX(a) < EX(b)) continue;
            if (TY(a) == 6 && TY(b) == 6 && LV(a) == LV(b) && EX(a) == EX(b) && ID(a) > ID(b)) continue;
            if (TY(a) != 6 && TY(b) != 6 && EX(a) < EX(b)) continue;
            if (TY(a) != 6 && TY(b) != 6 && EX(a) == EX(b) && ID(a) > ID(b)) continue;
            { E t = *(E*)((u8*)o->v.data + jo); *(E*)((u8*)o->v.data + jo) = o->v.data[k]; o->v.data[k] = t; }
        }
    }
    {
        E* e = o->v.data;
        e->p = fn_80006E1C();
        e->p[1] = (u32)(e->u + 0x28);
        e->p[0x11] = (u32)fn_8000BD3C(fn_800F4544(e->u, "\x91\xD2\x8B\x40"));
        e->p[0] |= 0xE021A000;
        fn_80006F20(e->p);
    }
    {
        u8 n;
        int io;
        for (i = o->x78 - 5, io = i * 8; i < (n = o->x78); i++, io += 8) {
            u8* q = fn_800C6210(fn_801246A4(*(u8**)((u8*)o->v.data + io)), 1);
            *(u32*)(q + 0x48) |= 0x400;
            o->x7C[(u16)(n - i - 1)] = q;
        }
    }
    if (fn_8024BCA0()[0x34] >= 2) o->x34 = 1;
}
#pragma use_lmw_stmw off
}
