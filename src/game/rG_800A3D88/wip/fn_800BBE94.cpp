// WIP, does not match: 56/880 lines, right size, masked diff empty. Only registers: the pointers of the two outer CurF loops (qa4, qa3, qa4b) take r28/r27 where r17/r18 are wanted, pushing the inner counters down. Declaration order (sw, rr, pair moves) does not reach it.
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
void* fn_800A6F34(int, int);
int fn_800A6D7C(void*, int, int);
int fn_80008C98(Mdl*, int);
u16 fn_80008CF0(Mdl*, int);
void* fn_800E45B0(int);
int fn_800E46C4(void*, int);
int fn_800A8208(const char*);
void* fn_800A7324(int, int, int);
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
#define STR(n) (lbl_803657E8 + (n))
struct W3 { u32 a, b, c; };
struct Mtx34 { f32 m[3][4]; };
union VU { Vec v; W3 w; };
struct InfoQ { u8 p[8]; u16 m8; };
struct PData { u8 p[4]; s16 m4; u8 p6[8]; u8 mE; u8 pf[9]; u32 m18; u8 p1c[0xC]; Vec m28; Vec m34; u8 p40[0x9C-0x40]; void* m9c; void* mA0; u8 pA4[0xC4-0xA4]; InfoQ* mC4; };
struct PA { u8 p[0x30]; PData* m30; };
struct MdlQ { u32 flags; };
struct ChrQ { u8 p[0x30]; MdlQ* mdl; u8 p34[0x58-0x34]; s16 m58, m5a; u8 p5c[0x78-0x5c]; void* data; u8 p7c[4]; ChrQ* m80; };
struct EffQ { u8 p[0x38]; struct { u8 p[0x21]; u8 m21; }* m38; };
int fn_801CFA90(void*);
int fn_801CFF0C(void*, int);
void* fn_800A7E34(int);
int fn_800C0A50(Eff*);
PA* fn_800E3810(int, ChrQ*);
void fn_800E461C(int);
int fn_80007630(MdlQ*, const char*);
int fn_800B4000(ChrQ*, int, Vec*, int, int);
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
void fn_800E48C8(PA*, Vec*);
void fn_800E4A40(PA*, f32);
void fn_800E49AC(PA*, f32);
void fn_800E4904(PA*, int, void*);
void fn_800E48F0(PA*, int, int);
void fn_800BB520(void*);
void fn_800BBAE0(void*);
static inline int Node(ChrQ* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
#define ZERO(r) r.w.a = 0; r.w.b = 0; r.w.c = 0;
#define AIM(o, r, k, vv, mt) \
    ZERO(r) \
    fn_800B4000(o, Node(o, STR(0x26)), &r.v, -1, 0); \
    vv.w = r.w; \
    k.x = 0.0f; \
    k.y = fn_800A7370(o->data, STR(0x16D)); \
    k.z = fn_800A7370(o->data, STR(0x176)); \
    fn_80312654(&mt, 0x79, 0.017453292f * fn_8001E064(o->m58)); \
    fn_80312DB4(&mt, &k, &k); \
    fn_80313460(&vv.v, &k, &vv.v);
#define PD(p) ((p)->m30)
int fn_800BBE94(ChrQ* c, void* sc, u32 fr) {
    Mtx34 m1; Mtx34 m2; Mtx34 m3;
    VU arg1; VU w1; VU w2; VU arg2; VU arg3; VU w3; VU w4;
    VU v1; Vec k1; VU r1; VU s1; VU r2; VU s2; VU r3; Vec k3; VU v3; VU r4; VU s4; VU r5; VU r6; VU s6; VU v7; Vec k7; VU r7; VU s7;
/*P*/
ChrE* qa3;
ChrE* qa4;
Eff* x;
int a0;
ChrE* qa4b;
int j3;
Eff* y;
int j2;
int a3;
PA* p;
ChrQ* o;
int a4x;
int a2b;
ChrE* q3b;
int a1a;
int n;
ChrE* q1;
int j1;
int a1b;
int j0b;
int st;
int j0;
int a0b;
int j2b;
int a2;
int a4b;
int j1b;
int a3b;
ChrE* qa2b;
ChrE* qa1;
ChrE* q2;
ChrE* q2b;
ChrE* qa2;
ChrE* q1b;
ChrE* qa3b;
int j3b;
ChrE* qa1b;
ChrE* q3;
/*E*/
#define CE ((ChrE*)c)
    o = c->m80;
    if (o == NULL) return 0;
    x = CurF(CE, a4x, qa4, a3, qa3, a2, qa2, a1a, qa1, a0, j3, q3, j2, q2, j1, q1, j0, x);
    if (x == NULL) return 0;
    {
        int r3v;
        if (sc != NULL) {
            void* t = fn_800A7E34(fn_801CFF0C(sc, fn_801CFA90(sc)));
            if (t != NULL) {
                if (*(int*)((u8*)t + 0x10) != 0) {
                    r3v = *(int*)((u8*)t + 0x10);
                    goto have;
                }
            }
        }
        y = CurF(CE, a4b, qa4b, a3b, qa3b, a2b, qa2b, a1b, qa1b, a0b, j3b, q3b, j2b, q2b, j1b, q1b, j0b, y);
        if (y == NULL) r3v = 0;
        else r3v = fn_800C0A50(y);
    have:
        if (r3v == 0) return 0;
        p = fn_800E3810(r3v, c);
    }
    if (p == NULL) return 0;
    fn_800E461C(1);
    n = -1;
    st = fn_800C09E0(x, -1);
    switch (st) {
    case 9:
    case 0xD:
        if (((EffQ*)x)->m38->m21 & 1) n = Node(c, STR(0x312));
        AIM(o, r1, k1, v1, m1)
        s1.w = v1.w;
        s1.v.y = fn_8001E064(o->m5a);
        arg1.w = s1.w;
        fn_800E48C8(p, &arg1.v);
        ZERO(r2)
        fn_800B4000(c, Node(c, STR(0x26)), &r2.v, -1, 0);
        s2.w = r2.w;
        s2.v.y = fn_8001E064(c->m5a);
        w1.w = s2.w;
        PD(p)->m28 = w1.v;
        AIM(o, r3, k3, v3, m2)
        w2.w = v3.w;
        PD(p)->m34 = w2.v;
        break;
    case 8:
        if (PD(p)->mC4->m8 & 0x80) {
            ZERO(r4)
            fn_800B4000(c, Node(c, STR(0x26)), &r4.v, -1, 0);
            s4.w = r4.w;
            s4.v.y = fn_8001E064(c->m5a);
            arg2.w = s4.w;
            fn_800E48C8(p, &arg2.v);
        } else {
            ZERO(r5)
            fn_800B4000(c, Node(c, STR(0x26)), &r5.v, -1, 0);
            arg3.w = r5.w;
            fn_800E48C8(p, &arg3.v);
        }
        ZERO(r6)
        fn_800B4000(c, Node(c, STR(0x26)), &r6.v, -1, 0);
        s6.w = r6.w;
        s6.v.y = fn_8001E064(c->m5a);
        w3.w = s6.w;
        PD(p)->m28 = w3.v;
        AIM(o, r7, k7, v7, m3)
        s7.w = v7.w;
        s7.v.y = fn_8001E064(o->m5a);
        w4.w = s7.w;
        PD(p)->m34 = w4.v;
        fn_800E4A40(p, (f32)fr);
        break;
    }
    fn_800E49AC(p, fn_8001E064(c->m58));
    PD(p)->mE = 3;
    fn_800E4904(p, 0, c);
    fn_800E48F0(p, 1, n);
    fn_800E48F0(p, 2, st);
    fn_800E4904(p, 3, sc);
    PD(p)->m4 = 1;
    PD(p)->m9c = (void*)fn_800BB520;
    PD(p)->mA0 = (void*)fn_800BBAE0;
    PD(p)->m18 |= 0x200;
    if (c->mdl != NULL) c->mdl->flags |= 8;
    return 1;
}
}
