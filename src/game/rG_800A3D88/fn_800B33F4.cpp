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
#define CUR2(c) (y = Cur(c, k3, r3, k2, r2, k1, r1, k0, y))
#define LOCS Eff* y; int k3; int k2; int k1; int k0; Eff* x; int j0; int j1; int j2; int j3; ChrE* q3; ChrE* q2; ChrE* q1; ChrE* r3; ChrE* r2; ChrE* r1;
struct NmE { u8 p[4]; const char* name; };
NmE* fn_800A81AC(int);
NmE* fn_800A82C8(int);
void fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(const char*);
void* fn_8000BDB0(const char*, int);
int fn_8000A0A8(void*, int);
void fn_8000BE20(void*);
extern char lbl_803657E8[];
int fn_800B6E2C(ChrE* c, int k, int a) {
            int j0; int k3; int j1; Eff* y; int j2; int k2; Eff* x; int k1; int j3; int k0; ChrE* q1; ChrE* r3; ChrE* q2; ChrE* r2; ChrE* q3; ChrE* r1;
    char buf[0x40];
    void* r;
    if (c->data == 0) r = NULL;
    else if (k < 0) r = NULL;
    else {
        CUR(c);
        r = fn_800A7324(c->data, x != NULL ? fn_800C09E0(x, c->m57) : 0, k);
    }
    if (r == NULL) return 0;
    int ok;
    if (c->data == 0) ok = 0;
    else {
        CUR2(c);
        int s = y != NULL ? fn_800C09E0(y, c->m57) : 0;
        if (fn_800A7324(c->data, s, k) == NULL) ok = 0;
        else {
            NmE* m = fn_800A81AC(s);
            fn_80290DDC(buf, lbl_803657E8 + 0x7C, ((NmE*)c->data)->name, fn_800A82C8(k)->name, m->name);
            ok = fn_8023F9F4(buf) != 0x40000;
        }
    }
    if (!ok) return 0;
    void* h = fn_8000BDB0(buf, (c->m50 & 0x4000000) ? 0xA0 : 0x2080);
    int v = fn_8000A0A8(h, a);
    fn_8000BE20(h);
    return v;
}
int fn_800B69D8(ChrE* c, int k) {
        int j0; int k3; int j1; Eff* y; int j2; int k2; Eff* x; int k1; int j3; int k0; ChrE* q1; ChrE* r3; ChrE* q2; ChrE* r2; ChrE* q3; ChrE* r1;
    char buf[0x40];
    void* r;
    if (c->data == 0) r = NULL;
    else if (k < 0) r = NULL;
    else {
        CUR(c);
        r = fn_800A7324(c->data, x != NULL ? fn_800C09E0(x, c->m57) : 0, k);
    }
    if (r == NULL) return 0;
    int ok;
    if (c->data == 0) ok = 0;
    else {
        CUR2(c);
        int s = y != NULL ? fn_800C09E0(y, c->m57) : 0;
        if (fn_800A7324(c->data, s, k) == NULL) ok = 0;
        else {
            NmE* m = fn_800A81AC(s);
            fn_80290DDC(buf, lbl_803657E8 + 0x7C, ((NmE*)c->data)->name, fn_800A82C8(k)->name, m->name);
            ok = fn_8023F9F4(buf) != 0x40000;
        }
    }
    if (!ok) return 0;
    int res = 0;
    void* h = fn_8000BDB0(buf, (c->m50 & 0x4000000) ? 0xA0 : 0x2080);
    if (fn_8000A0A8(h, 0xC) > 0) res = 1;
    if (fn_8000A0A8(h, 0x33) > 0) res = 1;
    fn_8000BE20(h);
    return res;
}
int fn_801CFA90(void*);
const char* fn_801CFF0C(void*, int);
struct Fx10 { u8 p[0x10]; int m10; };
Fx10* fn_800A7E34(const char*);
#if TARGET_PC
FE10_PROTO p32ret fn_800C0A50(Eff*);
#else
int fn_800C0A50(Eff*);
#endif
int fn_800BBB1C(ChrE* c, void* s) {
    int a0; int j3; int j2; int a1; int j1; int j0; ChrE* q3; ChrE* q2; ChrE* qa3; int a4; int a3; int a2; Eff* x; ChrE* q1; ChrE* qa4; ChrE* qa2; ChrE* qa1;
    if (s != NULL) {
        Fx10* f = fn_800A7E34(fn_801CFF0C(s, fn_801CFA90(s)));
        if (f != NULL && f->m10 != 0) return f->m10;
    }
    CURF(c);
    if (x == NULL) return 0;
    return fn_800C0A50(x);
}
f32 fn_8001E064(s16);
s16 fn_8001E094(f32);
void fn_800B3138(ChrE*);
f32 fn_800B8FF8(ChrE*);
void fn_800BFA4C(Eff*);
struct Cx { u8 p[0x30]; Mdl* mdl; u8 p34[0x44-0x34]; f32 m44; u8 p48[0x5C-0x48]; s16 m5c; };
extern const f32 lbl_804CD3B8;
void fn_800B33F4(ChrE* c, int a) {
        int k3; Eff* y; int k2; int j2; int k1; ChrE* qi; Eff* x; int j1; int j0; int j3; int k0; ChrE* r3; ChrE* q1; int i; ChrE* r2; ChrE* q2; ChrE* q3; ChrE* r1;
    if (c->mdl == NULL) return;
    fn_800B3138(c);
    if (a != 0) {
        f32 d = fn_800B8FF8(c);
        if (lbl_804CD3B8 != d) {
            ((Cx*)c)->m44 += d;
            fn_800B3138(c);
            c->m50 |= 0x10;
        }
    }
    *(int*)((u8*)c->mdl + 0x84) = fn_8001E094(fn_8001E064(((Cx*)c)->m5c));
    for (qi = c, i = 0; i < 2; i++, ADV(qi)) {
        x = E4(c, i, qi, j3, q3, j2, q2, j1, q1, j0, x);
        if (x != NULL) {
            y = E4(c, i, qi, k3, r3, k2, r2, k1, r1, k0, y);
            fn_800BFA4C(y);
        }
    }
}
int fn_800F18BC(Mdl*);
int fn_800BCC5C(ChrE* c, int k) {
    int j0; int j1; int j2; Eff* x; int j3; ChrE* q3; ChrE* q2; ChrE* q1;
    char buf[0x40];
    if (c->mdl == NULL) return 0;
    int r = 0;
    if (k < 0) {
        r = fn_800F18BC(c->mdl);
    } else {
    int ok;
    if (c->data == 0) ok = 0;
    else {
        CUR(c);
        int s = x != NULL ? fn_800C09E0(x, c->m57) : 0;
        if (fn_800A7324(c->data, s, k) == NULL) ok = 0;
        else {
            NmE* m = fn_800A81AC(s);
            fn_80290DDC(buf, lbl_803657E8 + 0x7C, ((NmE*)c->data)->name, fn_800A82C8(k)->name, m->name);
            ok = fn_8023F9F4(buf) != 0x40000;
        }
    }
    if (ok) {
        void* h = fn_8000BDB0(buf, (c->m50 & 0x4000000) ? 0xA0 : 0x2080);
        void* sv = *(void**)((u8*)c->mdl + 0x44);
        *(void**)((u8*)c->mdl + 0x44) = h;
        r = fn_800F18BC(c->mdl);
        *(void**)((u8*)c->mdl + 0x44) = sv;
        fn_8000BE20(h);
    }
    }
    return r;
}
long long OSGetTime();
void fn_80011CBC(void (*)(void*), void*);
void fn_8023F1A8(void*);
void* fn_8023F1A4(const char*, int);
int fn_800B1B48(ChrE*, int, int, u16, int);
int fn_800B54DC(ChrE* c, int k) {
    int j0; int j1; int j2; Eff* x; int j3; ChrE* q3; ChrE* q2; ChrE* q1;
    char buf[0x40];
    OSGetTime();
    int ok;
    if (c->data == 0) ok = 0;
    else {
        if (k < 0) {
            CUR(c);
            k = x != NULL ? fn_800C09E0(x, c->m57) : 0;
        }
        NmE* e = fn_800A81AC(k);
        if (e == NULL) ok = 0;
        else {
            fn_80290DDC(buf, lbl_803657E8 + 0x6F, ((NmE*)c->data)->name, e->name);
            ok = fn_8023F9F4(buf) != 0x40000;
        }
    }
    if (!ok) return 0;
    if (c->m38 != NULL) {
        fn_80011CBC(fn_8023F1A8, c->m38);
        c->m38 = NULL;
    }
    c->m38 = fn_8023F1A4(buf, (c->m50 & 0x4000000) ? 0xA0 : 0x2080);
    if (c->m7c != NULL) fn_800B1B48(c, fn_800A8208(lbl_803657E8 + 0x1BC), 0, 0, -1);
    OSGetTime();
    return 1;
}
}
