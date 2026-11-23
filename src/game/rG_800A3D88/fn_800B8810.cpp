#include "game/rG_800A3D88/chr.h"

// Battle character functions that inline the fn_800B5784 effect lookup.

extern "C" {
struct Eff {
    u8 pad[0x38];
    struct { u8 p[0x1C]; void* m1c; }* m38;
    u8 pad3c[0x46 - 0x3C];
    u16 m46;
};
struct ChrE {
    u8 pad[0x30];
    Mdl* mdl;
    u8 p34[4];
    void* m38;
    Eff* e[2];
    u8 p44[0x50-0x44];
    u32 m50;
    u8 p54[3];
    s8 m57;
    u8 p58[6];
    s8 m5e;
    u8 p5f[0x19];
    int data;
    void* m7c;
    ChrE* m80x;
    u8 p84[0x98-0x84];
    void* m98;
};
int fn_800C09E0(Eff*, int);
Eff* fn_800B5784(ChrE* c, int i);
#if TARGET_PC
FE10_PROTO void* fn_800A6F34(p32arg, int);
FE10_PROTO unsigned char * fn_800A6D7C(void*, int, int);
#else
void* fn_800A6F34(int, int);
int fn_800A6D7C(void*, int, int);
#endif
int fn_80008C98(Mdl*, int);
u16 fn_80008CF0(Mdl*, int);
void* fn_800E45B0(int);
int fn_800E46C4(void*, int);
int fn_800A8208(const char*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7324(p32arg, int, int);
#else
void* fn_800A7324(int, int, int);
#endif
/* Stand-in for fn_800B5784 inlined four levels deep at a call site. The compiler
   would only inline one level here, so the levels are written out by hand and
   their counters and pointers are caller locals, because that declaration
   order is what fixes the register order. Almost certainly not the original source. */
#define LIVE(x) ((x) != NULL && (x)->m38 != NULL && fn_800C09E0((x), -1) != 0xF)
#define ADV(q) (q = (ChrE*)((u8*)q + 4))
static inline Eff* E1(ChrE* c, int i, ChrE* q, int& j0, Eff*& x) {
    if (i < 0) {
        for (j0 = 0; j0 < 2; j0++) {
            x = fn_800B5784(c, j0);
            if (LIVE(x)) return x;
        }
        return NULL;
    }
    return q->e[0];
}
static inline Eff* E2(ChrE* c, int i, ChrE* q, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    if (i < 0) {
        for (q1 = c, j1 = 0; j1 < 2; j1++, ADV(q1)) {
            x = E1(c, j1, q1, j0, x);
            if (LIVE(x)) return x;
        }
        return NULL;
    }
    return q->e[0];
}
static inline Eff* E3(ChrE* c, int i, ChrE* q, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    if (i < 0) {
        for (q2 = c, j2 = 0; j2 < 2; j2++, ADV(q2)) {
            x = E2(c, j2, q2, j1, q1, j0, x);
            if (LIVE(x)) return x;
        }
        return NULL;
    }
    return q->e[0];
}
static inline Eff* Cur(ChrE* c, int& j3, ChrE*& q3, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    for (q3 = c, j3 = 0; j3 < 2; j3++, ADV(q3)) {
        x = E3(c, j3, q3, j2, q2, j1, q1, j0, x);
        if (LIVE(x)) return x;
    }
    return NULL;
}
#define CUR_LOCALS int j0; int j1; int j2; Eff* x; int j3; ChrE* q3; ChrE* q2; ChrE* q1;
#define CUR(c) (x = Cur(c, j3, q3, j2, q2, j1, q1, j0, x))
static inline Eff* E4(ChrE* c, int i, ChrE* q, int& j3, ChrE*& q3, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    if (i < 0) {
        for (q3 = c, j3 = 0; j3 < 2; j3++, ADV(q3)) {
            x = E3(c, j3, q3, j2, q2, j1, q1, j0, x);
            if (LIVE(x)) return x;
        }
        return NULL;
    }
    return q->e[0];
}
#define STATE_F(x) ((x) != NULL && (x)->m38 != NULL && fn_800C09E0((x), -1) == 0xF)
#define LOCALS2 int a0; int a1; int a2; int a3; int a4; ChrE* qa4; ChrE* qa3; ChrE* qa2; ChrE* qa1; Eff* x; int j3; int j2; int j1; int j0; ChrE* q3; ChrE* q2; ChrE* q1;
/* Prefers an effect in state 0xF, otherwise the current one. */
static inline Eff* CurF(ChrE* c, int& a4, ChrE*& qa4, int& a3, ChrE*& qa3, int& a2, ChrE*& qa2, int& a1, ChrE*& qa1, int& a0,
                        int& j3, ChrE*& q3, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    for (qa4 = c, a4 = 0; a4 < 2; a4++, ADV(qa4)) {
        x = E4(c, a4, qa4, a3, qa3, a2, qa2, a1, qa1, a0, x);
        if (STATE_F(x)) return x;
    }
    return Cur(c, j3, q3, j2, q2, j1, q1, j0, x);
}
#define CURF(c) (x = CurF(c, a4, qa4, a3, qa3, a2, qa2, a1, qa1, a0, j3, q3, j2, q2, j1, q1, j0, x))
#pragma use_lmw_stmw on
#define D5 Eff* x; int a0; int j3; int a1; int j2; int a2; int j1; int a3; int j0; int a4; ChrE* q3; ChrE* qa3; ChrE* q2; ChrE* qa4; ChrE* q1; ChrE* qa2; ChrE* qa1;
int fn_800C0EE4(Eff*);
void fn_800BF608(Eff*, int, int);
static inline int Moving(ChrE* c, int k) {
    if (c->mdl == NULL) return 0;
    return fn_80008C98(c->mdl, k);
}
static inline s16 Frame(ChrE* c, int k) {
    if (c->mdl == NULL) return -1;
    return fn_80008CF0(c->mdl, k);
}
int fn_800B8810(ChrE* c) {
            int a0; int a1; int j2; int a2; int j1; int j3; int j0; int a3; int a4; ChrE* q3; ChrE* q2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa3; ChrE* qa2; u16 f; ChrE* qa1;
    if (Moving(c, 0xE) != 0) {
        f = Frame(c, 0xE);
        CURF(c);
        if (x == NULL) return 0;
        if (fn_800C0EE4(x) != 0) return 0;
        fn_800BF608(x, f, -1);
        return 1;
    }
    return 0;
}
struct Fxc { u8 p[0xC]; const char* mC; };
struct Sb { u8 m0, m1; s16 m2; };
int fn_801CFA90(Sb*);
int fn_801CFB7C(Sb*);
int fn_801CFED8(Sb*, int);
int fn_801CFCE0(Sb*);
const char* fn_801CFF0C(Sb*, int);
Fxc* fn_800A7E34(const char*);
const char* fn_800C0A18(Eff*);
const char* fn_800C0A34(Eff*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(p32arg, const char*);
#else
void* fn_800A7460(int, const char*);
#endif
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
const char* fn_800BAB5C(ChrE* c, Sb* s) {
    int a0; int a1; int j2; int a2; int j1; int j3; int j0; int a3; int a4; ChrE* q3; ChrE* q2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa3; ChrE* qa2; ChrE* qa1;
    CURF(c);
    if (s == NULL) {
        if (x != NULL) return fn_800C0A18(x);
        return NULL;
    }
    if (fn_801CFA90(s) != 0) {
        Fxc* f = fn_800A7E34(fn_801CFF0C(s, fn_801CFA90(s)));
        if (f != NULL && f->mC != NULL) return f->mC;
    }
    if (fn_801CFB7C(s) != 0) {
        Fxc* f = fn_800A7E34(fn_801CFF0C(s, fn_801CFB7C(s)));
        if (f != NULL && f->mC != NULL) return f->mC;
    }
    if (fn_801CFED8(s, 0x7E) != 0) return STR(0x2C8);
    if (c->m80x != NULL) {
        switch (s->m2) {
        case 0x6E: case 0x6F:
            if (fn_801CFCE0(s) != 0) return STR(0x2D7);
            break;
        case 0x70:
            if (fn_800A7460(c->m80x->data, STR(0x2E3)) != NULL) return STR(0x2D7);
            break;
        }
    }
    switch (s->m1) {
    case 0: case 2: case 6: break;
    case 1: case 3: case 4: case 5: case 7:
        switch (s->m2) {
        case 0x6F:
            if (x != NULL && fn_800C0A34(x) != NULL) return fn_800C0A34(x);
            return STR(0x2EC);
        case 0x6E:
            if (x != NULL && fn_800C0A18(x) != NULL) return fn_800C0A18(x);
            return STR(0x2F8);
        }
        break;
    }
    return NULL;
}
}
