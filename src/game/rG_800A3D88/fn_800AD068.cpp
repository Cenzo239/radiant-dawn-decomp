#include "game/rG_800A3D88/chr.h"

// Battle scene controller: damage applied to the target.
extern "C" {
struct Sc { u8 m0; u8 m1; s16 m2; u8 p4[4]; u8 m8, m9; u8 pA; u8 mB; u8 mC; u8 pD; u16 mE[1]; };
struct UP { u8 p[6]; s16 m6; u8 p8[2]; s16 mA; };
struct Ch { u8 pad[0x50]; u32 m50; s8 m54; s8 m55; };
struct Gg { u8 pad[0x3A]; s16 m3a; s16 m3c; u8 p3e[2]; f32 m40; u8 m44; u8 p45[0x50 - 0x45]; s16 from; s16 to; u32 t; u32 n; s16 m5c; };
struct Bat {
    u8 p[0x44];
    void* m44;
    u8 p48[0x5C - 0x48];
    Gg* m5c[2];
    u8 p64[0x69 - 0x64];
    s8 m69;
    u8 m6a, m6b, m6c;
    u8 p6d[0x83 - 0x6D];
    u8 m83; u8 m84; u8 m85;
    Sc* m88;
};
struct Sg { u8 p[0x15EC]; u32 flags; };
extern Sg lbl_803C8E80;
extern char lbl_80365488[];
extern u8 lbl_80382220[];
#define STR(n) (lbl_80365488 + (n))
struct W3 { u32 a, b, c; };
struct PP { u8 p[0x34]; int m34; int m38; f32 m3c; };
struct QQ { u8 p[0x3E]; s16 m3e; };
void fn_800BB074(Ch*, Sc*);
void fn_800A4BDC(void*, int);
int fn_800B727C(Ch*, const char*);
int fn_800B5CDC(Ch*);
int fn_800B1B48(Ch*, int, int, u16, int);
void fn_800BD024(Ch*, const char*);
UP* fn_801D0784(Sc*, int);
f32 fn_8017F68C(int, f32, f32, f32, f32);
int fn_8028DB44(int);
u32 fn_8028C1A0(f32);
void fn_800B38F0(W3*, Ch*, int);
void fn_800B377C(Vec*, Ch*, int);
void fn_800EE61C(W3*, int, Bat*);
int fn_801CFE78(Sc*, u16);
void fn_800AADBC(Bat*, u16);
int fn_801CFA90(Sc*);
f32 fn_800A84A4(const char*);
PP* fn_80081050(void*, void*);
QQ* fn_8017C218(int, void*);
void fn_800BCF10(Ch*);
void fn_802549C4(const char*, Vec*, f32);
static inline int GgCur(Gg* g) {
    if (g->t == 0) return g->from;
    if (g->t == g->n) return g->to;
    return (int)fn_8017F68C(0, g->from, g->to, g->t, g->n);
}
static inline int Hp(Sc* s, int k) { return fn_801D0784(s, k)->mA; }
static inline void Gg_Set(Gg* g, int hp) {
    f32 f = fn_8028DB44((s16)hp - (s16)GgCur(g)) * 0x30;
    g->from = GgCur(g);
    g->to = hp;
    g->t = 0;
    g->n = fn_8028C1A0(f / 16.666666f);
}
static inline void Shake(Gg* g, s16 m, f32 x, u8 on) {
    g->m3a = 0;
    g->m3c = m;
    g->m40 = x;
    g->m44 = on;
}
struct FAD068 { Vec r0, a0, r1, a1, r2, a2; W3 r3, a3; };
void fn_800AD068(Bat* p, Ch* a, Ch* c, int mode) {
    FAD068 f;
Gg* g;
int s;
int i;
int k2;
bool isF;
int hp;
int type;
u16 id;
int o;
int d;
    p->m6b++;
    type = p->m88->m2;
    isF = type == 0x6F;
    fn_800BB074(a, p->m88);
    fn_800A4BDC(p->m44, type);
    if (mode >= 0) {
        int k = p->m69;
        switch (mode) {
        case 0: k = fn_800B727C(c, STR(0xAE)); break;
        case 1: k = fn_800B727C(c, STR(0x16E)); break;
        case 2: k = fn_800B727C(c, STR(0x173)); break;
        }
        if (k < 0) k = fn_800B727C(c, STR(0xAE));
        int fl = 0xFFFF;
        if (fn_800B5CDC(c)) fl = 0x41;
        if (fn_800B1B48(c, k, -1, fl, -1)) fn_800BD024(c, STR(0x49));
        if (p->m6b < p->m6a) c->m50 |= 0x800;
        else c->m50 &= ~0x800;
    }
    if (p->m6b == p->m6a) {
        k2 = c->m55;
        s = c->m54;
        fn_801D0784(p->m88, k2);
        hp = Hp(p->m88, k2);
        if (hp < 0) hp = 0;
        { UP* u = fn_801D0784(p->m88, k2); u->m6 = hp; }
        if (p->m83 != 0) {
            g = p->m5c[s];
            d = hp - g->to;
            Gg_Set(g, hp);
            if (isF) {
                Shake(g, 0x1E, 4.0f * ((f32)d / (f32)g->m5c) + 3.0f, 0);
            } else {
                Shake(g, 0x15, 4.0f * ((f32)d / (f32)g->m5c) + 2.0f, 1);
            }
            if (d != 0) {
                fn_800B38F0(&f.r3, c, -1);
                f.a3 = f.r3;
                fn_800EE61C(&f.a3, d, p);
            }
        }
        for (i = 0, o = 0; i < p->m88->mC; o += 2, i++) {
            id = *(u16*)((u8*)p->m88->mE + o);
            if (fn_801CFE78(p->m88, id)) fn_800AADBC(p, id);
        }
        f32 t = 0.0f;
        int n = 0;
        int e = 0;
        if (fn_801CFA90(p->m88)) {
            t = fn_800A84A4(STR(0x17C));
            n = (int)fn_800A84A4(STR(0x18B));
            e = (int)fn_800A84A4(STR(0x19A));
        }
        if (p->m88->m8 != 0) {
            t = fn_800A84A4(STR(0x1A9));
            n = (int)fn_800A84A4(STR(0x1B8));
            e = (int)fn_800A84A4(STR(0x1C7));
            if (lbl_803C8E80.flags & 0x200000) {
                n <<= 3;
                t *= 0.125f;
            }
            c->m50 |= 0x200000;
        }
        if (n > 0) {
            if (n != 0) {
                PP* q = fn_80081050(lbl_80382220, p);
                q->m3c = t;
                q->m34 = n;
                q->m38 = e;
            }
            if (p->m88->m8 != 0) {
                if (lbl_803C8E80.flags & 0xC00000) {
                    QQ* q = fn_8017C218(3, p);
                    if (q != NULL) q->m3e = n;
                    q = fn_8017C218(6, p);
                    if (q != NULL) q->m3e = n;
                } else {
                    QQ* q = fn_8017C218(0, p);
                    if (q != NULL) q->m3e = n;
                }
            }
        }
    }
    fn_800BCF10(c);
    if (isF) {
        fn_800B377C(&f.r2, c, -1);
        f.a2 = f.r2;
        fn_802549C4(STR(0x1D6), &f.a2, 0.0f);
    } else {
        fn_800B377C(&f.r1, c, -1);
        f.a1 = f.r1;
        fn_802549C4(STR(0x1EE), &f.a1, 0.0f);
    }
    if (p->m88->m8 != 0) {
        fn_800B377C(&f.r0, c, -1);
        f.a0 = f.r0;
        fn_802549C4(STR(0x203), &f.a0, 0.0f);
    }
}
}
