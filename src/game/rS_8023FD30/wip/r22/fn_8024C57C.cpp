/*
 * fn_8024C57C (round 22 draft, `other`). Static initialiser (__sinit) of the save-worker file: it
 * constructs the two big file statics of the pool at lbl_80427810 (see fn_8024B450.cpp for the pool
 * layout: sHeader +0x0, sData0 +0x10, sData1 +0x1BF0) and registers both for destruction.
 *
 * Object A (SaveWork, at pool +0x10 = lbl_80427820, 0x1BCC bytes; destructor fn_8024CCB8, record at
 * lbl_80427810):
 *   - embedded serialisable values: vtable lbl_80391160 ({vt, 8 bytes}: save/load fn_8024CC5C /
 *     fn_8024CC70, which call fn_8008A780 with size 8) at +0x1C, +0x18C4, +0x18D0, +0x18DC; vtable
 *     lbl_8037F7E0 ({vt, 16 bytes}: fn_80063BE0 / fn_80063C08, size 0x10) at +0x28, +0x189C, +0x18B0;
 *   - an array of 30 elements of 0x18 bytes at +0x18F8 whose constructor and Reset() (fn_8024CCAC)
 *     both set byte +8 to -1;
 *   - then the constructor body (an inlined Clear()): four -1 words at +0, zeroes, two arrays of
 *     0x300 words at +0x3C and +0xC3C, 0x60 bytes at +0x183C, the value payloads, -1 halfwords and a
 *     {-1,-1,-1,-1} halfword quad at +0x18E8..+0x18F6 (the four 0xFFFF halfwords at
 *     lbl_804D0018..lbl_804D001E, copied through a stack temporary: a local aggregate), a call to
 *     fn_801E74CC(), Reset() on every element through a pointer to member (the {0, -1, fn_8024CCAC}
 *     constant lbl_80391170 and __ptmf_scall fn_8028C178, i.e. std::for_each with mem_fun_ref),
 *     byte +0x1BC8 = fn_80244D88(), byte +0x1BC9 = -1.
 * Object B (at pool +0x1BF0 = lbl_80429400, 0x1070 bytes; destructor fn_8019FAC8, record at pool
 *   +0x1BE0): vtable lbl_80391150 at +0x3C, member at +0x44 constructed by fn_801095FC, -1 in the
 *   words at +0..+0xC and byte +0x32, zero at +0x10, +0x14, +0x40, then fn_8017F44C(B + 0x70, -1, 0x1000).
 *
 * What differs from the original code: the original is compiler-generated from the class
 * definitions (constructor stores scheduled together, the peeled first element, the 8x unrolled
 * element loop with its trip-count test, 24x and 48x unrolled clear loops). This is a hand-written
 * function with the same stores in loops, so the instruction sequence is different (`other`); the
 * effect on memory and the calls (arguments and order) are the same.
 *
 * Port: define the classes and the two globals; their constructors do the above. The pointer to
 * member and the destructor registration are ordinary C++.
 */
#include "game/rS_8023FD30/types.h"
#pragma use_lmw_stmw off

struct Value8 {             /* serialisable 8-byte value, vtable lbl_80391160 */
    const void* vt;
    u32 v[2];
};

struct Value16 {            /* serialisable 16-byte value, vtable lbl_8037F7E0 */
    const void* vt;
    u32 v[4];
};

struct Elem18 {
    u8 pad0[8];
    s8 x8;                  /* +0x08: -1 = unused */
    u8 pad9[0xF];
    Elem18() { x8 = -1; }
    void Reset();           /* fn_8024CCAC: x8 = -1 */
};

struct Quad16 { s16 a, b, c, d; };

struct SaveWork {
    s32 w0[4];              /* +0x0000 */
    u32 w10, w14;           /* +0x0010 */
    u8 pad18[4];
    Value8 v1c;             /* +0x001C */
    Value16 v28;            /* +0x0028 */
    u32 a3c[0x300];         /* +0x003C */
    u32 aC3C[0x300];        /* +0x0C3C */
    u8 b183c[0x60];         /* +0x183C */
    Value16 v189c;          /* +0x189C */
    Value16 v18b0;          /* +0x18B0 */
    Value8 v18c4;           /* +0x18C4 */
    Value8 v18d0;           /* +0x18D0 */
    Value8 v18dc;           /* +0x18DC */
    s16 h18e8, h18ea, h18ec;
    Quad16 q18ee;           /* +0x18EE */
    s16 h18f6;              /* +0x18F6 */
    Elem18 elems[30];       /* +0x18F8 */
    u8 b1bc8;               /* +0x1BC8 */
    s8 b1bc9;               /* +0x1BC9 */
    u8 pad1bca[2];
};

struct SaveB {              /* 0x1070 bytes */
    s32 w0[4];              /* +0x00 */
    u32 w10, w14;           /* +0x10 */
    u8 pad18[0x32 - 0x18];
    s8 b32;                 /* +0x32 */
    u8 pad33[0x3C - 0x33];
    const void* vt;         /* +0x3C */
    u32 w40;                /* +0x40 */
    u8 m44[0x70 - 0x44];    /* +0x44: constructed by fn_801095FC */
    u8 m70[0x1070 - 0x70];  /* +0x70: fn_8017F44C(m70, -1, 0x1000) */
};

struct DtorRecord { void* next; void* dtor; void* obj; };

struct SavePool {
    DtorRecord recA;        /* +0x0000 lbl_80427810 */
    u8 pad0c[4];
    SaveWork a;             /* +0x0010 lbl_80427820 */
    u8 pad1bdc[4];
    DtorRecord recB;        /* +0x1BE0 */
    u8 pad1bec[4];
    SaveB b;                /* +0x1BF0 lbl_80429400 */
};

extern "C" {
extern SavePool lbl_80427810;
extern const u8 lbl_80391150[], lbl_80391160[], lbl_8037F7E0[];
extern const s16 lbl_804D0018, lbl_804D001A, lbl_804D001C, lbl_804D001E;
void fn_801E74CC(void);
s32 fn_80244D88(void);
void fn_801095FC(void* o);
void fn_8017F44C(void* p, int a, int size);
s32 fn_8024CCB8(void* p, s32 del);
void* fn_8019FAC8(void* p, int del);
void* __register_global_object(void* obj, void* dtor, void* rec);
}

static inline void Clear(SaveWork* w)
{
    int i;
    Quad16 q = {lbl_804D0018, lbl_804D001A, lbl_804D001C, lbl_804D001E};
    void (Elem18::*reset)() = &Elem18::Reset;
    w->w0[1] = -1;
    w->w0[0] = -1;
    w->w0[2] = -1;
    w->w0[3] = -1;
    w->w14 = 0;
    w->w10 = 0;
    w->v1c.v[0] = 0;
    w->v1c.v[1] = 0;
    w->v28.v[0] = 0;
    w->v28.v[1] = 0;
    w->v28.v[2] = 0;
    w->v28.v[3] = 0;
    for (i = 0; i < 0x300; i++) {
        w->a3c[i] = 0;
        w->aC3C[i] = 0;
    }
    for (i = 0; i < 0x60; i++) {
        w->b183c[i] = 0;
    }
    w->v189c.v[0] = 0;
    w->v189c.v[1] = 0;
    w->v189c.v[2] = 0;
    w->v189c.v[3] = 0;
    w->v18b0.v[0] = 0;
    w->v18b0.v[1] = 0;
    w->v18b0.v[2] = 0;
    w->v18b0.v[3] = 0;
    w->v18c4.v[0] = 0;
    w->v18c4.v[1] = 0;
    w->v18d0.v[0] = 0;
    w->v18d0.v[1] = 0;
    w->v18dc.v[0] = 0;
    w->v18dc.v[1] = 0;
    w->h18e8 = -1;
    w->h18ea = -1;
    w->h18ec = -1;
    w->q18ee = q;
    w->h18f6 = -1;
    fn_801E74CC();
    for (Elem18* e = w->elems; e != w->elems + 30; e++) {
        (e->*reset)();
    }
    w->b1bc8 = fn_80244D88();
    w->b1bc9 = -1;
}

static inline void Value8Ctor(Value8* v) { v->vt = lbl_80391160; v->v[0] = 0; v->v[1] = 0; }

static inline void Value16Ctor(Value16* v)
{
    v->vt = lbl_8037F7E0;
    v->v[0] = 0;
    v->v[1] = 0;
    v->v[2] = 0;
    v->v[3] = 0;
}

extern "C" void fn_8024C57C(void)
{
    SaveWork* w = &lbl_80427810.a;
    SaveB* b = &lbl_80427810.b;
    int i;
    Quad16 q = {lbl_804D0018, lbl_804D001A, lbl_804D001C, lbl_804D001E};

    /* member constructors */
    Value8Ctor(&w->v1c);
    Value16Ctor(&w->v28);
    Value16Ctor(&w->v189c);
    Value16Ctor(&w->v18b0);
    Value8Ctor(&w->v18c4);
    Value8Ctor(&w->v18d0);
    Value8Ctor(&w->v18dc);
    w->h18e8 = -1;
    w->h18ea = -1;
    w->h18ec = -1;
    w->q18ee = q;
    w->h18f6 = -1;
    for (i = 0; i < 30; i++) {
        w->elems[i].x8 = -1;
    }
    /* constructor body */
    Clear(w);
    __register_global_object(w, (void*)fn_8024CCB8, &lbl_80427810.recA);

    b->vt = lbl_80391150;
    fn_801095FC(b->m44);
    b->w0[1] = -1;
    b->w0[0] = -1;
    b->w0[2] = -1;
    b->w0[3] = -1;
    b->w14 = 0;
    b->w10 = 0;
    b->b32 = -1;
    b->w40 = 0;
    fn_8017F44C(b->m70, -1, 0x1000);
    __register_global_object(b, (void*)fn_8019FAC8, &lbl_80427810.recB);
}
