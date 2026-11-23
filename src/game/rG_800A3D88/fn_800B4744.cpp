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
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
struct Eff5 { u8 p[0x46]; u16 m46; };
void fn_80081A90(Eff*);
#if TARGET_PC
FE10_PROTO p32ret fn_800A7FAC(int);
#else
int fn_800A7FAC(int);
#endif
#if TARGET_PC
FE10_PROTO int fn_800A6844(p32arg, int);
#else
int fn_800A6844(int, int);
#endif
int fn_800A7EEC(const char*);
#if TARGET_PC
FE10_PROTO int fn_800A7460(p32arg, const char*);
#else
int fn_800A7460(int, const char*);
#endif
Eff* fn_800BF138(ChrE*);
void fn_800C1184(Eff*, int);
void fn_800BF148(Eff*);
void fn_800BF750(Eff*, ChrE*, const char*);
static inline void Mk(ChrE* c, int i, int s, const char* col, Eff*& x) {
    if (c->mdl != NULL && c->data != 0) {
        if (c->e[i] != NULL) fn_80081A90(c->e[i]);
        c->e[i] = NULL;
        x = fn_800BF138(c);
        c->e[i] = x;
        fn_800C1184(x, s);
        if (c->m50 & 0x04000000) ((Eff5*)x)->m46 |= 0x80;
        if (!fn_800A7460(c->data, STR(0x198))) {
            fn_800BF148(x);
            fn_800BF750(x, c, col);
        }
        if (fn_800A7460(c->data, STR(0x1A1))) ((Eff5*)x)->m46 |= 0x20;
    }
}
void fn_800B4744(ChrE* c, int s, int a) {
/*P*/
int z9;
int j0;
int z;
int j1;
int j2;
Eff* x;
ChrE* q;
Eff* x1;
Eff* x2;
Eff* x3;
Eff* x4;
Eff* x5;
int k;
int j3;
int j;
Eff* y1;
Eff* y2;
Eff* y4;
const char* c1;
const char* c2;
const char* c3;
const char* c4;
const char* c5;
ChrE* q9;
ChrE* q3;
ChrE* q2;
ChrE* q1;
int s2;
int o5;
/*E*/
    const char* t[3] = { "r_hand", "l_hand", "arrow" };
    CUR(c);
    if (x != NULL) {
        switch (fn_800C09E0(x, -1)) {
        case 9: case 10: case 11:
            q = c;
            j = 0;
            z = 0;
            for (; j < 2; j++, ADV(q)) {
                if (q->e[0] != NULL) fn_80081A90(q->e[0]);
                q->e[0] = (Eff*)z;
            }
            break;
        }
    }
    s2 = fn_800A7FAC(s);
    if (s2 == 0) return;
    switch ((u8)fn_800A6844(s2, -1)) {
    case 10: {
        int b = fn_800A7EEC(STR(0x195));
        c1 = t[1]; Mk(c, 0, s, c1, x1);
        Mk(c, 1, b, t[0], y1);
        break;
    }
    case 11: {
        int b = fn_800A7EEC(STR(0x1AA));
        Mk(c, 0, s, t[0], y2);
        c2 = t[2]; Mk(c, 1, b, c2, x2);
        break;
    }
    case 9:
        c3 = t[1]; Mk(c, 1, s, c3, x3);
        break;
    default:
        if (fn_800A7460(c->data, STR(0x1B5))) {
            Mk(c, 0, s, t[0], y4);
            c4 = t[1]; Mk(c, 1, s, c4, x4);
        } else {
            o5 = a << 2; c5 = *(const char**)((u8*)t + o5);
            if (c->mdl != NULL && c->data != 0) {
                if (a < 0) {
                    q9 = c;
                    k = 0;
                    z9 = 0;
                    for (; k < 2; k++, ADV(q9)) {
                        if (q9->e[0] != NULL) fn_80081A90(q9->e[0]);
                        q9->e[0] = (Eff*)z9;
                    }
                } else {
                    a = (int)((u8*)c + o5);
                    if (*(Eff**)(a + 0x3C) != NULL) fn_80081A90(*(Eff**)(a + 0x3C));
                    *(Eff**)(a + 0x3C) = NULL;
                }
                x5 = fn_800BF138(c);
                *(Eff**)((u8*)c + o5 + 0x3C) = x5;
                fn_800C1184(x5, s);
                if (c->m50 & 0x04000000) ((Eff5*)x5)->m46 |= 0x80;
                if (!fn_800A7460(c->data, STR(0x198))) {
                    fn_800BF148(x5);
                    fn_800BF750(x5, c, c5);
                }
                if (fn_800A7460(c->data, STR(0x1A1))) ((Eff5*)x5)->m46 |= 0x20;
            }
        }
        break;
    }
}
}
