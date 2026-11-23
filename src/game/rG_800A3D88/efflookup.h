#ifndef RG_EFFLOOKUP_H
#define RG_EFFLOOKUP_H
#include "game/rG_800A3D88/chr.h"

/* Hand-unfolded copy of the fn_800B5784 effect lookup, see NOTES.md. Loop counters,
   pointers and results are caller locals passed by reference, because their
   declaration order is what fixes the registers. Not the original source. */
struct Col {
    u8 r, g, b, a;
    Col() {}
    Col(u32 v) { r = v >> 24; g = v >> 16; b = v >> 8; a = v; }
};
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
    u8 p44[0x50 - 0x44];
    u32 m50;
    u8 p54[3];
    s8 m57;
    u8 p58[6];
    s8 m5e;
    u8 p5f[0x19];
    int data;
    void* m7c;
    u8 p80[0x98 - 0x80];
    void* m98;
};
extern "C" {
int fn_800C09E0(Eff*, int);
Eff* fn_800B5784(ChrE* c, int i);
}
#define LIVE(x) ((x) != NULL && (x)->m38 != NULL && fn_800C09E0((x), -1) != 0xF)
#define STATE_F(x) ((x) != NULL && (x)->m38 != NULL && fn_800C09E0((x), -1) == 0xF)
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
static inline Eff* Cur(ChrE* c, int& j3, ChrE*& q3, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    for (q3 = c, j3 = 0; j3 < 2; j3++, ADV(q3)) {
        x = E3(c, j3, q3, j2, q2, j1, q1, j0, x);
        if (LIVE(x)) return x;
    }
    return NULL;
}
#define CUR(c) (x = Cur(c, j3, q3, j2, q2, j1, q1, j0, x))
static inline Eff* CurF(ChrE* c, int& a4, ChrE*& qa4, int& a3, ChrE*& qa3, int& a2, ChrE*& qa2, int& a1, ChrE*& qa1, int& a0,
                        int& j3, ChrE*& q3, int& j2, ChrE*& q2, int& j1, ChrE*& q1, int& j0, Eff*& x) {
    for (qa4 = c, a4 = 0; a4 < 2; a4++, ADV(qa4)) {
        x = E4(c, a4, qa4, a3, qa3, a2, qa2, a1, qa1, a0, x);
        if (STATE_F(x)) return x;
    }
    return Cur(c, j3, q3, j2, q2, j1, q1, j0, x);
}
#define CURF(c) (x = CurF(c, a4, qa4, a3, qa3, a2, qa2, a1, qa1, a0, j3, q3, j2, q2, j1, q1, j0, x))
#endif
