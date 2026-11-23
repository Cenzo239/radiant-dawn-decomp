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
    u8 p80[0x98-0x80];
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
void* fn_800B7468(ChrE* c) {
    CUR_LOCALS
    CUR(c);
    return x != NULL ? x->m38->m1c : 0;
}
int fn_800B591C(ChrE* c) {
    CUR_LOCALS
    CUR(c);
    if (x == NULL) return 0;
    return fn_800C09E0(x, c->m57);
}
void* fn_800B196C(ChrE* c, const char* name) {
    CUR_LOCALS
    int k = fn_800A8208(name);
    if (c->data == 0) return 0;
    if (k < 0) return 0;
    CUR(c);
    return fn_800A7324(c->data, x != NULL ? fn_800C09E0(x, c->m57) : 0, k);
}
static inline void* Slot(ChrE* c) {
    if (c->data == NULL) return NULL;
    if (c->m57 < 0) return NULL;
    return fn_800A6F34(c->data, c->m57);
}

#if TARGET_PC
FE10_PROTO p32ret fn_800A80F8(p32arg);
FE10_PROTO int fn_800A67EC(p32arg);
#else
int fn_800A80F8(int);
int fn_800A67EC(int);
#endif
void fn_800B4744(ChrE*, int, int);
void fn_800C1218(Eff*, int*);
void fn_800B4574(ChrE* c, int* p, int a) {
    CUR_LOCALS
    if (p == NULL || *p == 0) return;
    int r = fn_800A80F8(*p);
    if (r != 0) {
        fn_800B4744(c, fn_800A67EC(r), a);
        CUR(c);
        if (x != NULL) fn_800C1218(x, p);
    }
}
int fn_800B727C(ChrE* c, const char* name) {
    CUR_LOCALS
    int k = fn_800A8208(name);
    void* r;
    if (c->data == 0) r = NULL;
    else if (k < 0) r = NULL;
    else {
        CUR(c);
        r = fn_800A7324(c->data, x != NULL ? fn_800C09E0(x, c->m57) : 0, k);
    }
    int v = -1;
    if (r != NULL) v = k;
    return v;
}
int fn_800BD024(ChrE* c, const char* name) {
    int k; int j3; int j2; int j1; int j0; Eff* x; ChrE* q3; ChrE* q2; ChrE* q1;
    k = fn_800A8208(name);
    void* r;
    if (c->data == 0) r = NULL;
    else if (k < 0) r = NULL;
    else {
        CUR(c);
        r = fn_800A7324(c->data, x != NULL ? fn_800C09E0(x, c->m57) : 0, k);
    }
    if (r == NULL) return 0;
    c->m5e = k;
    return 1;
}
void fn_800C0988(Eff*);
void fn_800B5010(ChrE* c) {
            int a0; int j3; int j2; int a1; int j1; int j0; ChrE* q3; ChrE* q2; ChrE* qa3; int a4; int a3; int a2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa2; ChrE* qa1;
    CURF(c);
    if (x != NULL) fn_800C0988(x);
}
static inline int Moving(ChrE* c, int k) {
    Mdl* m = c->mdl;
    if (m == NULL) return 0;
    return fn_80008C98(m, k);
}
int fn_800B5DF0(ChrE* c, u16* out) {
        int a0; int j3; int j2; int a1; int j1; int j0; ChrE* q3; ChrE* q2; ChrE* qa3; int a4; int a3; int a2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa2; ChrE* qa1;
    *out = 0;
    if (c->mdl == NULL) return 0;
    if (Moving(c, 0)) {
        *out = fn_80008CF0(c->mdl, 0);
        return 1;
    }
    CURF(c);
    if (x != NULL && (x->m46 & 4)) return 1;
    void* q = fn_800E45B0(1);
    if (q != NULL && fn_800E46C4(q, 0)) return 1;
    return 0;
}
int fn_800B61B0(ChrE* c, u16* out) {
        int a0; int j3; int j2; int a1; int j1; int j0; ChrE* q3; ChrE* q2; ChrE* qa3; int a4; int a3; int a2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa2; ChrE* qa1;
    *out = 0;
    if (c->mdl == NULL) return 0;
    if (Moving(c, 1)) {
        *out = fn_80008CF0(c->mdl, 1);
        return 1;
    }
    CURF(c);
    if (x != NULL && (x->m46 & 4)) return 1;
    void* q = fn_800E45B0(1);
    if (q != NULL && fn_800E46C4(q, 1)) return 1;
    return 0;
}
struct M30 { u8 pad[0x18]; u32 m18; };
struct M98 { u8 pad[0x30]; M30* m30; };
void fn_800B056C(ChrE* c) {
            int k3; Eff* y; int k2; int j2; int k1; ChrE* qi; Eff* x; int j1; int j0; int j3; int k0; ChrE* r3; ChrE* q1; int i; ChrE* r2; ChrE* q2; ChrE* q3; ChrE* r1;
    c->m50 &= ~1;
    for (qi = c, i = 0; i < 2; i++, ADV(qi)) {
        x = E4(c, i, qi, j3, q3, j2, q2, j1, q1, j0, x);
        if (x != NULL) {
            y = E4(c, i, qi, k3, r3, k2, r2, k1, r1, k0, y);
            y->m46 &= ~1;
        }
    }
    if (c->m98 != NULL) {
        ((M98*)c->m98)->m30->m18 &= ~0x10;
    }
}
void fn_800B08B0(ChrE* c) {
    int k3; Eff* y; int k2; int j2; int k1; ChrE* qi; Eff* x; int j1; int j0; int j3; int k0; ChrE* r3; ChrE* q1; int i; ChrE* r2; ChrE* q2; ChrE* q3; ChrE* r1;
    c->m50 |= 1;
    for (qi = c, i = 0; i < 2; i++, ADV(qi)) {
        x = E4(c, i, qi, j3, q3, j2, q2, j1, q1, j0, x);
        if (x != NULL) {
            y = E4(c, i, qi, k3, r3, k2, r2, k1, r1, k0, y);
            y->m46 |= 1;
        }
    }
    if (c->m98 != NULL) {
        ((M98*)c->m98)->m30->m18 |= 0x10;
    }
}
}
