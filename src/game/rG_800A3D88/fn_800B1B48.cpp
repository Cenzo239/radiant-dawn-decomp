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
#define STR(n) (lbl_803657E8 + (n))
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
struct BfA { u32 a:9; u32 x:2; u32 r:21; };
struct BfB { u32 a:23; u32 y:1; u32 r:8; };
extern const f32 lbl_804CD3B8;
#define K0 lbl_804CD3B8
struct Arc { u8 p[4]; f32 m4, m8, mC, m10, m14; };
struct Nm { u8 p[4]; const char* m4; u16 m8; u8 mA; };
struct DataZ { u8 p[4]; const char* m4; };
struct MdlB { u32 flags; u8 p4[0x44-4]; void* m44; u8 p48[0x58-0x48]; f32 frame; u8 p5c[0x78-0x5c]; f32 m78; };
struct ChrB { u8 p[0x30]; MdlB* mdl; u8 p34[0x44-0x34]; Vec m44; u32 m50; u8 p54[3]; s8 m57; u8 p58[6]; s8 m5e; u8 m5f; u8 p60; u8 m61; u8 p62[2]; f32 m64; u8 p68[0x78-0x68]; DataZ* data; Nm* m7c; u8 p80[0x94-0x80]; Arc* m94; };
void* fn_800A81AC(int);
Nm* fn_800A82C8(int);
void fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(char*);
int fn_800A6B7C(Nm*);
void* fn_8017C288(ChrB*);
void fn_8017C1AC(void*, int);
void* fn_800A64A0();
void fn_800A4BBC(void*);
void fn_800BF568(Eff*, int);
f32 fn_800A84A4(const char*);
f32 fn_800A7370(DataZ*, const char*);
int fn_80007630(MdlB*, const char*);
int fn_800B4000(ChrB*, int, Vec*, int, int);
#if TARGET_PC
FE10_PROTO struct GAnim * fn_8000BDB0(char*, int);
FE10_PROTO void fn_800088B0(MdlB*, p32arg);
#else
int fn_8000BDB0(char*, int);
void fn_800088B0(MdlB*, int);
#endif
void fn_800087FC(MdlB*, int);
void fn_80007DE8(MdlB*);
void fn_800B3138(ChrB*);
void fn_80008B50(MdlB*);
void fn_80009150(MdlB*, char*, int);
void fn_8000866C(MdlB*, f32);
void fn_800B33F4(ChrB*, int);
void fn_800F18BC(MdlB*);
static inline int Node(ChrB* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
#define CB ((ChrE*)c)
int fn_800B1B48(ChrB* c, int id, int fr, int mode, int k) {
    char buf[0x44];
    Vec vA; Vec vB;
    VU t1; VU t2; VU t3; VU t4;
    VU r1; VU r2; VU r3; VU r4;
    VU pos;
/*P*/
ChrE* q1b;
ChrE* q3c;
int j0a;
int j3b;
int j3c;
int j1a;
Eff* xb;
Eff* xc;
int j2a;
int j2b;
int j2c;
Eff* xa;
int j1b;
int j1c;
int j3a;
int j0b;
int j0c;
int f;
int to;
ChrE* q2a;
ChrE* q2b;
ChrE* q2c;
ChrE* q3a;
ChrE* q3b;
ChrE* q1c;
ChrE* q1a;
int s;
/*E*/
    if (c->mdl == NULL) return 0;
    {
        void* r;
        s = k;
        if (c->data == NULL) r = NULL;
        else if (id < 0) r = NULL;
        else {
            if (k < 0) {
                xa = Cur(CB, j3a, q3a, j2a, q2a, j1a, q1a, j0a, xa);
                s = xa != NULL ? fn_800C09E0(xa, c->m57) : 0;
            }
            r = fn_800A7324((int)c->data, s, id);
        }
        if (r == NULL) return 0;
    }
    {
        int ok;
        if (c->data == NULL) ok = 0;
        else {
            if (k < 0) {
                xb = Cur(CB, j3b, q3b, j2b, q2b, j1b, q1b, j0b, xb);
                k = xb != NULL ? fn_800C09E0(xb, c->m57) : 0;
            }
            if (fn_800A7324((int)c->data, k, id) == NULL) ok = 0;
            else {
                DataZ* a = (DataZ*)fn_800A81AC(k);
                Nm* b = fn_800A82C8(id);
                fn_80290DDC(buf, STR(0x7C), c->data->m4, b->m4, a->m4);
                ok = fn_8023F9F4(buf) != 0x40000;
            }
        }
        if (!ok) return 0;
    }
    if (id == 0 && c->m7c != NULL && id == fn_800A6B7C(c->m7c)) return 1;
    c->m50 &= ~0x100;
    c->m50 &= ~0x600000;
    c->m5e = -1;
    c->m5f = 0;
    c->mdl->flags &= ~4;
    {
        void* t = fn_8017C288(c);
        if (t != NULL) fn_8017C1AC(t, -1);
    }
    if (c->m50 & 0x4000) {
        fn_800A4BBC(fn_800A64A0());
        c->m50 &= ~0x4000;
    }
    xc = Cur(CB, j3c, q3c, j2c, q2c, j1c, q1c, j0c, xc);
    if (xc != NULL) fn_800BF568(xc, -1);
    {
        Nm* e = fn_800A82C8(id);
        c->m7c = e;
        u16 fl = e->m8;
        if (!(fl & 1)) {
            if (fl & 8) c->m50 &= ~4;
            else c->m50 |= 4;
        }
    }
    if (fr < 0) {
        if (c->data == NULL) fr = 0;
        else if (c->m7c == NULL) fr = 0;
        else {
            f = c->m7c->mA;
            if (c->m50 & 0x02000000) f = (int)fn_800A84A4(STR(0xC8));
            if (c->m7c->m8 & 4) f = (int)(f * fn_800A7370(c->data, STR(0xD5)));
            fr = (int)(f * fn_800A7370(c->data, STR(0xDE)));
        }
    }
    if (fr > 0xFF) fr = 0xFF;
    if (c->mdl->m44 != NULL && fr > 0) {
        to = (int)(c->mdl->frame + (f32)fr);
        r1.w.a = 0; r1.w.b = 0; r1.w.c = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &r1.v, to, 0);
        t1.w = r1.w;
        vA = t1.v;
        fn_800088B0(c->mdl, fn_8000BDB0(buf, (c->m50 & 0x04000000) ? 0xA0 : 0x2080));
        fn_800087FC(c->mdl, mode);
        c->mdl->m78 = 1.0f;
        c->mdl->frame = c->mdl->frame + (f32)fr;
        fn_80007DE8(c->mdl);
        fn_800B3138(c);
        r2.w.a = 0; r2.w.b = 0; r2.w.c = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &r2.v, -1, 0);
        t2.w = r2.w;
        c->mdl->m78 = 0.0f;
        c->mdl->frame = c->mdl->frame - (f32)fr;
        vB = t2.v;
        fn_80007DE8(c->mdl);
        fn_800B3138(c);
        Arc* a = c->m94;
        f32 d = vA.x - vB.x;
        a->m8 = 0.0f; a->mC = 0.0f; a->m10 = 0.0f; a->m14 = 0.0f;
        a->m4 = d;
        a->m14 = (f32)fr;
        c->m61 = fr;
        c->m64 = -1.0f;
        c->m50 |= 0x100;
    } else {
        r3.w.a = 0; r3.w.b = 0; r3.w.c = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &r3.v, -1, 0);
        t3.w = r3.w;
        vA = t3.v;
        fn_80008B50(c->mdl);
        fn_80009150(c->mdl, buf, (c->m50 & 0x04000000) ? 0xA0 : 0x2080);
        fn_8000866C(c->mdl, 0.0f);
        fn_800087FC(c->mdl, mode);
        fn_80007DE8(c->mdl);
        fn_800B3138(c);
        if (c->m7c->m8 & 0x100) {
            r4.w.a = 0; r4.w.b = 0; r4.w.c = 0;
            fn_800B4000(c, Node(c, STR(0x26)), &r4.v, -1, 0);
t4.w = r4.w; pos.w = *(W3*)&c->m44; vB = t4.v;
f32 d = vA.x - vB.x; f32 z = pos.v.z + K0; f32 y = pos.v.y + K0; c->m44.x = pos.v.x + d; c->m44.y = y; c->m44.z = z;
            fn_800B33F4(c, 1);
        }
    }
    if (c->mdl != NULL) fn_800F18BC(c->mdl);
    return 1;
}
}
