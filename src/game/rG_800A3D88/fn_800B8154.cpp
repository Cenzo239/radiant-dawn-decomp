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

#pragma use_lmw_stmw off
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
struct W3 { u32 a, b, c; };
struct Mtx34 { f32 m[3][4]; };
union VU { Vec v; W3 w; };
int fn_80008E88(Mdl*, int, int);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChrE*, int, Vec*, int, int);
#if TARGET_PC
FE10_PROTO f32 fn_800A7370(p32arg, const char*);
#else
f32 fn_800A7370(int, const char*);
#endif
f32 fn_800A84A4(const char*);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
void fn_803134A8(f32, Vec*, Vec*);
void fn_800C0478(Eff*, Vec*, int);
static inline int Node(ChrE* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
#define ANG(o) (0.017453292f * fn_8001E064(((Chr5*)(o))->m58))
struct Chr5 { u8 p[0x58]; s16 m58; u8 p5a[0x80-0x5a]; ChrE* m80; };
#define MBASE(o,r0,ka,va,mt,base) \
    r0.w.a = 0; r0.w.b = 0; r0.w.c = 0; \
    fn_800B4000(o, Node(o, STR(0x26)), &r0.v, -1, 0); \
    *(W3*)&va = r0.w; \
    ka.x = 0.0f; \
    ka.y = fn_800A7370(o->data, STR(0x16D)); \
    ka.z = fn_800A7370(o->data, STR(0x176)); \
    fn_80312654(&mt, 0x79, ANG(o)); \
    fn_80312DB4(&mt, &ka, &ka); \
    fn_80313460(&va, &ka, &va);
int fn_800B8154(ChrE* c) {
    Mtx34 m1; Mtx34 m2; Mtx34 m3;
    Vec res;
    VU off;
    VU v1; VU v2; VU v3;
    Vec arg;
    VU r0a; Vec ka; Vec va; VU r0b; Vec kb; Vec vb; VU z1; Vec z0;
/*P*/
Eff* x;
int j3;
int j2;
int d;
int a1;
int a0;
int a2;
int j1;
int a3;
int j0;
int a4;
ChrE* q3;
ChrE* qa3;
ChrE* q2;
ChrE* qa4;
ChrE* q1;
ChrE* qa2;
int fr;
ChrE* qa1;
ChrE* o;
/*E*/
    if (c->mdl == NULL ? 0 : fn_80008C98(c->mdl, 0x12)) {
        CURF(c);
        if (x == NULL) return 0;
        fr = (int)c->mdl->frame;
        d = fn_80008E88(c->mdl, fr, 0x13) - fr;
        o = ((Chr5*)c)->m80;
        if (o != NULL) {
            MBASE(o, r0a, ka, va, m1, baseA)
            v1.w = *(W3*)&va;
            res = v1.v;
        } else {
            MBASE(c, r0b, kb, vb, m2, base)
            v2.w = *(W3*)&vb;
            res = v2.v;
            f32 f = fn_800A84A4(STR(0x11F));
            W3* p;
            if (c->data == 0) {
                *(u32*)&z0.x = 0; *(u32*)&z0.y = 0; *(u32*)&z0.z = 0;
                v3.w = *(W3*)&z0;
                p = &v3.w;
            } else {
                z1.w.a = 0; z1.w.b = 0; z1.w.c = 0;
                z1.v.z = fn_800A7370(c->data, STR(0x1CE));
                fn_80312654(&m3, 0x79, ANG(c));
                fn_80312DB4(&m3, &z1.v, &z1.v);
                v3.w = z1.w;
                p = &v3.w;
            }
            off.w = *p;
            fn_803134A8(2.0f * f, &off.v, &off.v);
            fn_80313460(&res, &off.v, &res);
        }
        *(W3*)&arg = *(W3*)&res;
        fn_800C0478(x, &arg, d);
        return 1;
    }
    return 0;
}
}
