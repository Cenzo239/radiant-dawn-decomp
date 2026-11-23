/* Teardowns of a few procs and a small helper */
#include "game/rN_8025EEF0/calls.h"

#pragma auto_inline off

struct Slot { void* u; s16 a, b; };
struct Vec8 { u8* data; int size; };
struct Pair8x { int a; void* b; };

extern "C" {

extern Slot lbl_80430740[3][20];
void fn_800C4AA8(void* p);
void fn_8017AB5C(void* p, int a);
void fn_8011FE74(void* u, int a);
void fn_80011CBC(void* f, void* p);
void fn_80006EE0(void* p);
void fn_800C429C(void* p);
void fn_8012D6FC(void);
void fn_8012D744(void);
void fn_8012D820(void);
extern char lbl_80392F30[];
extern char lbl_80392ED8[];
extern int lbl_804CC108;

static inline void vecClear(Vec8* v) { int n = (v->data + v->size) - v->data; v->size -= n; }
static inline void vecFree3(Vec8* v) {
    if (v->data != 0) {
        vecClear(v);
        fn_80079210(v->data);
    }
}
static inline void vecFree2(Vec8* v) { if (v != 0) { vecFree3(v); } }
static inline void vecFree1(Vec8* v) { if (v != 0) { vecFree2(v); } }
static inline void vecFree(Vec8* v) { if (v != 0) { vecFree1(v); } }

struct Obj7F { u8 pad[0x34]; void* m34; u8 pad38[0x14]; Vec8 v; };
void fn_8027F7DC(Obj7F* p) {
    vecClear(&p->v);
    fn_8001D424(p->m34);
    if (p != 0) {
        vecFree(&p->v);
    }
}

class V14 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void v14(int del);
};
struct Pad28 { u8 pad[0x28]; };
class DtorObj : public Pad28 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};
struct Obj82 { u8 pad[0x30]; void* m30; void* m34; u8 pad38[0x18]; DtorObj* m50; Vec8 v; };
void fn_802827BC(Obj82* p) {
    fn_80081A90(p->m34);
    fn_8001D424(p->m30);
    if (p->m50 != 0) {
        p->m50->dtor(1);
    }
    if (p != 0) {
        vecFree(&p->v);
    }
}

struct Pair8 { int a; void* b; };
struct Obj86 { u8 pad[0x38]; void* m38; u8 pad3C[0x30]; Vec8 v; u8 pad74[4]; u8 m78; u8 pad79[3]; void* m7C[8]; };
void fn_80286A3C(Obj86* p) {
    Pair8* end;
    Pair8* q;
    int i;
    fn_8001D424(p->m38);
    q = (Pair8*)p->v.data;
    end = q + p->v.size;
    for (; q != end; q++) {
        if (q->b != 0) {
            fn_80011CBC(fn_80006EE0, q->b);
        }
    }
    vecClear(&p->v);
    for (i = p->m78 - 5; i < p->m78; i++) {
        void* o = p->m7C[(u16)(p->m78 - i - 1)];
        if (o != 0) {
            fn_800C429C(o);
        }
    }
    fn_8012D6FC();
    fn_8012D744();
    fn_8012D820();
    if (p != 0) {
        vecFree(&p->v);
    }
}

void* fn_8028BBD0(int a, void* b) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    if (f1 & 0x800000) {
        return 0;
    }
    if (f2 & 0x200000) {
        return fn_80081050(lbl_80392F30, (void*)7);
    }
    lbl_804CC108 = a != 0 ? 2 : 0;
    return fn_80081050(lbl_80392ED8, b);
}

}
