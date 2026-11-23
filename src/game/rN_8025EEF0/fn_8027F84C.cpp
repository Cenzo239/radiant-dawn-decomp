/* Proc owning a vector of 8-byte items: create, with vector::reserve(0x50) inlined */
#include "game/rN_8025EEF0/calls.h"


struct Item8 { int a; int b; };
struct W2a { int w[2]; };
struct VecI { Item8* data; int size; u32 cap; };

extern "C" {

extern u8 __files[];
extern char lbl_803929E8[];
extern char lbl_80392A48[];
extern char lbl_80392C90[];
extern char lbl_80392D00[];
void* fn_80079150(int n);
void fn_80290B48(void* f, const char* s, ...);
void fn_80291BD0(void);

static inline void vecClear(VecI* v) { int n = ((u8*)v->data + v->size) - (u8*)v->data; v->size -= n; }

static inline void vecDtor(VecI* v) {
    if (v->data != 0) {
        vecClear(v);
        fn_80079210(v->data);
    }
}

static inline void swapI(int& a, int& b) { int t = a; a = b; b = t; }

static inline void reserve(VecI* v, const char* msg) {
    if (v->cap < 0x50) {
        /*P*/
        VecI t;
        Item8* s;
        Item8* d;
        Item8* e;
        Item8* m;
/*E*/
        t.data = 0;
        t.size = 0;
        t.cap = 0;
        m = (Item8*)fn_80079150(0x280);
        if (m == 0) {
            fn_80290B48(__files + 0xA0, msg);
            fn_80291BD0();
        }
        t.data = m;
        t.cap = 0x50;
        e = v->data + v->size;
        d = m + t.size;
        s = v->data;
        for (; s < e; s++, d++) {
            if (d != 0) {
                *(W2a*)d = *(const W2a*)s;
            }
            t.size++;
        }
        v->size = 0;
        swapI(*(int*)&v->cap, *(int*)&t.cap);
        swapI(*(int*)&v->data, *(int*)&t.data);
        swapI(v->size, t.size);
        vecDtor(&t);
    }
}

struct Obj7F { u8 pad[0x38]; int m38; u8 pad3C[0x10]; VecI v; };

void fn_8027F84C(void* parent) {
    Obj7F* p = (Obj7F*)fn_80081194(lbl_803929E8, parent);
    if (p != 0) {
        p->v.data = 0;
        p->v.size = 0;
        p->v.cap = 0;
        reserve(&p->v, lbl_80392A48);
    }
    p->m38 = 0;
}

}
