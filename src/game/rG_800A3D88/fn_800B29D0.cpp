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

extern char lbl_803657E8[];
struct C4 { u8 r, g, b, a; };
struct Q4 { f32 x, y, z, w; };
struct Arc { u8 p[4]; f32 m4, m8, mC, m10, m14; };
struct EffZ { u8 p[0x46]; u16 m46; };
struct MdlZ { u8 p[0x18]; u32 m18; };
struct OwnZ { u8 p[0x30]; MdlZ* mdl; };
struct ChZ { u8 p[0x44]; Vec m44; u8 p50[4]; u32 m50x; };

void fn_80008F10(Mdl*, u8, u8, u8);
void fn_80008F20(Mdl*, u8);
void fn_800C11B8(Eff*, C4*);
void fn_800B33F4(ChrE*, int);
struct ChrY { u8 p[0x44]; Vec m44; u32 m50; u8 p54[2]; u8 m56; u8 p57; s16 m58, m5a, m5c; s8 m5e; u8 m5f; u8 p60; u8 m61; u8 p62[6]; Q4 m68; u8 p78[0x8C-0x78]; Arc* m8c; Arc* m90; Arc* m94; OwnZ* m98; };
static inline void Cl(Arc* a) { a->m4 = 0.0f; a->m8 = 0.0f; a->mC = 0.0f; a->m10 = 0.0f; a->m14 = 0.0f; }
#define LB lbl_804CD41C
#define LC (*(C4*)lbl_804CD41C)
void fn_800B29D0(ChrE* c0) {
    ChrY* cy = (ChrY*)c0;
    ChrE* c = c0;
    Vec z;
/*P*/
Eff* x;
int b3;
Eff* w;
Eff* v;
int a0;
int b2;
int e0;
int d0;
int a1;
int b1;
int i;
ChrE* q;
int e1;
int d1;
int a2;
int b0;
int e2;
int d2;
int a3;
Eff* y;
int e3;
int d3;
ChrE* qa1;
ChrE* qb1;
ChrE* qc1;
ChrE* qd3;
ChrE* qa2;
ChrE* qb2;
ChrE* qc2;
ChrE* qd2;
ChrE* qa3;
ChrE* qb3;
ChrE* qc3;
ChrE* qd1;
/*E*/
    *(u32*)&z.x = 0; *(u32*)&z.y = 0; *(u32*)&z.z = 0;
    cy->m44 = z;
    cy->m58 = 0; cy->m5a = 0; cy->m5c = 0;
    Q4 q4 = { 0.0f, 0.0f, 0.0f, 1.0f };
    cy->m68 = q4;
    cy->m5f = 0;
    cy->m56 = 0;
    cy->m5e = -1;
    cy->m61 = 0;
    Cl(cy->m8c);
    Cl(cy->m90);
    Cl(cy->m94);
    C4 k = { 0x80, 0x80, 0x80, 0xFF };
    if (c->mdl != NULL) {
        fn_80008F10(c->mdl, k.r, k.g, k.b);
        fn_80008F20(c->mdl, k.a);
        for (q = c, i = 0; i < 2; i++, ADV(q)) {
            x = E4(c, i, q, a3, qa3, a2, qa2, a1, qa1, a0, x);
            if (x != NULL) {
                y = E4(c, i, q, b3, qb3, b2, qb2, b1, qb1, b0, y);
                C4 t = k;
                fn_800C11B8(y, &t);
            }
        }
    }
    cy->m50 &= ~1;
    for (q = c, i = 0; i < 2; i++, ADV(q)) {
        w = E4(c, i, q, e3, qc3, e2, qc2, e1, qc1, e0, w);
        if (w != NULL) {
            v = E4(c, i, q, d3, qd3, d2, qd2, d1, qd1, d0, v);
            ((EffZ*)v)->m46 &= ~1;
        }
    }
    if (cy->m98 != NULL) cy->m98->mdl->m18 &= ~0x10;
    fn_800B33F4(c, 1);
}
}
