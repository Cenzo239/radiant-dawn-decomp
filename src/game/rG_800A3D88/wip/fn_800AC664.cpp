// WIP, does not match: 23/521 lines differ: second Hit inlining has c/sl swapped (r27/r28). Same-inline orders do not reach it.
#include "game/rG_800A3D88/chr.h"

// Battle scene controller: one state of the attack sequence.
extern "C" {
struct Sc { u8 m0; u8 m1; s16 m2; u8 p4[4]; u8 m8, m9; u8 pA; u8 mB; u8 mC; u8 pD; u16 mE[1]; };
struct UP { u8 p[6]; s16 m6; u8 p8[2]; s16 mA; };
struct Ch { u8 pad[0x54]; s8 m54; s8 m55; };
/* HP bar with a tween from m50 to m52, timer m54 of m58. */
struct Gg { u8 pad[0x50]; s16 from; s16 to; u32 t; u32 n; };
struct Bat {
    u8 p[0x44];
    void* m44;
    u8 p48[0x5C - 0x48];
    Gg* m5c[2];
    u8 p64[0x69 - 0x64];
    s8 m69;
    u8 m6a, m6b, m6c;
    u8 p6d[3];
    Ch* m70;
    Ch* m74;
    s8 m78;
    u8 p79[0x83 - 0x79];
    u8 m83; u8 m84; u8 m85;
    Sc* m88;
};
extern char lbl_80365488[];
#define STR(n) (lbl_80365488 + (n))
void fn_800B8810(Ch*);
int fn_800B6570(Ch*, u16*);
int fn_800BBE94(Ch*, Sc*, u16);
int fn_800BBB1C(Ch*, Sc*);
void fn_800A614C(void*, int);
f32 fn_800A84A4(const char*);
int fn_800B8154(Ch*);
int fn_800A5F08(void*, Ch*, int);
void fn_800A4B00(void*, Ch*);
void fn_800A47AC(void*, int);
int fn_801CFCE0(Sc*);
void fn_800B7F98(Ch*);
int fn_800B5DF0(Ch*, u16*);
int fn_800B61B0(Ch*, u16*);
int fn_801CFC58(Sc*);
int fn_801CFC0C(Sc*);
UP* fn_801D0784(Sc*, int);
f32 fn_8017F68C(int, f32, f32, f32, f32);
int fn_8028DB44(int);
u32 fn_8028C1A0(f32);
void fn_800BCF10(Ch*);
struct W3 { u32 a, b, c; };
void fn_800B38F0(W3*, Ch*, int);
void fn_800B377C(Vec*, Ch*, int);
void fn_800EE61C(W3*, int, Bat*);
void fn_800EE1BC(W3*, Bat*);
void fn_800AD068(Bat*, Ch*, Ch*, u16);
void fn_800AD740(Bat*, Ch*, Ch*);
int fn_801D04E4(void*);
int fn_800B1B48(Ch*, int, int, u16, int);
void fn_800BD024(Ch*, const char*);
int fn_801CFE78(Sc*, u16);
void fn_800AADBC(Bat*, u16);
void fn_802549C4(const char*, Vec*, f32);
int fn_800AD954(Bat*);
int fn_801D02FC(Sc*);
void fn_80083DC4(void*, int);
static inline BOOL IsLow(Bat* b) {
    switch (b->m78) {
    case 0: case 2: return 1;
    case 1: default: return 0;
    }
}
static inline int GgCur(Gg* g) {
    if (g->t == 0) return g->from;
    if (g->t == g->n) return g->to;
    return (int)fn_8017F68C(0, g->from, g->to, g->t, g->n);
}
static inline void Gg_Set(Gg* g, int hp) {
    f32 f = fn_8028DB44(hp - (s16)GgCur(g)) * 0x30;
    g->from = GgCur(g);
    g->to = hp;
    g->t = 0;
    g->n = fn_8028C1A0(f / 16.666666f);
}
static inline void Hit(Bat* p, W3* a, W3* r) {
/*P*/
int hp;
int d;
Gg* g;
int k;
int sl;
Ch* c;
/*E*/
    c = p->m70;
    k = c->m55;
    sl = c->m54;
    fn_801D0784(p->m88, k);
    hp = fn_801D0784(p->m88, k)->mA;
    fn_801D0784(p->m88, k)->m6 = hp;
    if (p->m83 != 0) {
        g = p->m5c[sl];
        d = hp - g->to;
        if (d != 0) {
            Gg_Set(g, hp);
            fn_800BCF10(c);
            fn_800B38F0(r, c, -1);
            *a = *r;
            fn_800EE61C(a, d, p);
        }
    }
}
/* One aggregate, because the temporaries sit in the reverse of the order this compiler gives them. */
struct FAC664 { u16 out; W3 a0, r0; Vec a1, r1; W3 a2, r2, a3, r3; };
int fn_800AC664(Bat* p) {
/*P*/
u16 id;
Ch* u;
int i;
int o;
/*E*/
    FAC664 f;
    f.out = 0;
    fn_800B8810(p->m70);
    if (fn_800B6570(p->m70, &f.out)) {
        if (fn_800BBE94(p->m70, p->m88, f.out)) {
            fn_800A614C(p->m44, fn_800BBB1C(p->m70, p->m88));
        }
        if ((s8)p->m88->m1 == 4) {
            p->m6c = (int)fn_800A84A4(STR(0xEF));
        }
    }
    if (fn_800B8154(p->m70)) {
        if (IsLow(p)) {
            p->m6c = 0;
        } else {
            p->m6c = (int)fn_800A84A4(STR(0xEF));
        }
    }
    if (p->m6c != 0 && (u8)--p->m6c == 0) {
        if (!fn_800A5F08(p->m44, p->m74, p->m69)) {
            fn_800A4B00(p->m44, p->m74);
            fn_800A47AC(p->m44, 0);
        }
    }
    switch (p->m88->m2) {
    case 0x6E:
    case 0x6F:
        if (!fn_801CFCE0(p->m88)) fn_800B7F98(p->m70);
        if (fn_800B5DF0(p->m70, &f.out)) {
            if (fn_801CFC58(p->m88)) {
                if (p->m6b == p->m6a) {
                    Hit(p, &f.a3, &f.r3);
                } else {
                    fn_800AD068(p, p->m70, p->m74, f.out);
                }
            } else if (fn_801CFCE0(p->m88)) {
                fn_800AD740(p, p->m70, p->m74);
            } else {
                fn_800AD068(p, p->m70, p->m74, f.out);
                if (p->m6b == p->m6a && fn_801CFC0C(p->m88)) {
                    Hit(p, &f.a2, &f.r2);
                }
            }
        }
        break;
    case 0x70:
        if (p->m84 != 0) {
            if (fn_801D04E4(p->m88)) {
                if (fn_800B61B0(p->m70, &f.out)) fn_800AD740(p, p->m70, p->m74);
            } else {
                if (fn_800B5DF0(p->m70, &f.out)) fn_800AD740(p, p->m70, p->m74);
            }
        } else {
            if (fn_800B61B0(p->m70, &f.out)) {
                u = p->m74;
                p->m6b++;
                if (fn_800B1B48(u, p->m69, -1, 0xFFFF, -1)) {
                    fn_800BD024(u, STR(0x49));
                }
                if (p->m6b == p->m6a) {
                    for (i = 0, o = 0; i < p->m88->mC; o += 2, i++) {
                        id = *(u16*)((u8*)p->m88->mE + o);
                        if (fn_801CFE78(p->m88, id)) fn_800AADBC(p, id);
                    }
                    if (p->m83 != 0) {
                        fn_800B38F0(&f.r0, u, -1);
                        f.a0 = f.r0;
                        fn_800EE1BC(&f.a0, p);
                    }
                }
                fn_800B377C(&f.r1, u, -1);
                f.a1 = f.r1;
                fn_802549C4(STR(0xFE), &f.a1, 0.0f);
            }
        }
        break;
    }
    if (fn_800AD954(p)) {
        switch (fn_801D02FC(p->m88)) {
        case 0x28:
            fn_80083DC4(p, 9);
            break;
        default:
            return 0;
        }
    }
    return 1;
}
}
