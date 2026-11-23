/* fn_8027F84C, fn_80287188: 42 positional words. vector::reserve(0x50) is inlined; element copy must load +0 into r3 and +4 into r0, and src/end/dst must be r7/r5/r6. */
/* Procs owning a vector of 8-byte items, with reserve(0x50) inlined */
#include "game/rN_8025EEF0/calls.h"


struct Item8 { int a; int b; };
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

static inline void vecClear(VecI* v) { int n = (v->data + v->size) - v->data; v->size -= n; }

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
        Item8* e;
        Item8* d;
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
        s = v->data;
        e = s + v->size;
        d = m + t.size;
        for (; s < e; s++, d++) {
            if (d != 0) {
                int y = s->b;
                int x = s->a;
                d->a = x;
                d->b = y;
            }
            t.size++;
        }
        v->size = 0;
        swapI(*(int*)&v->data, *(int*)&t.data);
        swapI(v->size, t.size);
        swapI(*(int*)&v->cap, *(int*)&t.cap);
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
        p->m38 = 0;
    }
}

struct Obj87 {
    u8 pad[0x30];
    u8 m30; u8 pad31;
    s16 m32;
    u8 m34;
    u8 pad35[0xF];
    int m44;
    s16 m48;
    u8 m4A;
    u8 m4B;
    s16 m4C;
    u8 m4E; u8 pad4F;
    s16 m50;
    s16 m52;
    s16 m54, m56, m58, m5A, m5C, m5E, m60, m62, m64;
    u8 pad66[4];
    s16 m6A;
    VecI v;
    u8 m78;
    u8 m79;
};

void fn_80287188(void* parent) {
    Obj87* p = (Obj87*)fn_80081194(lbl_80392C90, parent);
    if (p != 0) {
        p->m30 = 0;
        p->m32 = 0;
        p->m34 = 0;
        p->m44 = 0x1A4;
        p->m48 = 0x1E;
        p->m4A = 0;
        p->m4B = 1;
        p->m4C = 0x1E;
        p->m4E = 0;
        p->m50 = 0xFF;
        p->m52 = 0xFE;
        p->m6A = 0;
        p->v.data = 0;
        p->v.size = 0;
        p->v.cap = 0;
        p->m78 = 0;
        p->m79 = 0;
        reserve(&p->v, lbl_80392D00);
        p->m54 = 0;
        p->m56 = 0;
        p->m58 = 0;
        p->m5A = 0;
        p->m5C = 0;
        p->m5E = 0;
        p->m60 = 0;
        p->m62 = 0;
        p->m64 = 0;
    }
}

}
