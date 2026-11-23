#include "game/rG_800A3D88/chr.h"
extern "C" {
struct Sc { u8 p[1]; };
struct UP { void* u; u8 p4[2]; s16 m6; u8 p8[4]; s16 mC; u8 pe[2]; s16 m10, m12, m14, m16; };
struct G5 { u8 p[0x38]; u8 m38; u8 m39; u8 p3a[0x12]; u8 m4c; u8 p4d[3]; s16 m50, m52; int m54, m58; s16 m5c; u8 p5e[2]; int m60; void* m48; };
struct G5a { u8 p[0x48]; void* m48; u8 m4c; u8 p4d[3]; };
struct G3 { u8 p[0x38]; u8 m38; u8 p39[3]; int m3c; };
struct Gg { u8 p[0x33]; u8 m33; void* m34[2]; u8 m3c[2]; s16 m3e[2]; s16 m42[2]; s16 m46[2]; s16 m4a[2]; };
struct Un { u8 p[0xEC]; int ec; u8 pf0[4]; struct { u8 p[8]; u8 m8; }* f4; };
struct G5x { u8 p[0x38]; u8 m38, m39; u8 p3a[0xE]; Un* m48; u8 m4c; u8 p4d[3]; s16 m50, m52; int m54, m58; s16 m5c; u8 p5e[2]; int m60; };
struct Bat {
    u8 p[0x54];
    G3* m54[2];
    G5x* m5c[2];
    Gg* m64;
    u8 p68[0x83-0x68];
    u8 m83;
    u8 p84[4];
    Sc* m88;
};
#define SceneGlobal SceneGlobalX
struct SceneGlobal { u8 p[0x15EC]; u32 flags; };
extern SceneGlobal lbl_803C8E80;
int fn_801D0674(Sc*, int);
UP* fn_801D0784(Sc*, int);
Gg* fn_800C2DFC(void*);
G5x* fn_800C22B0(u8, Bat*);
G3* fn_800C3300(u8, Bat*);
u8 fn_8002C84C(SceneGlobal*, int);
#if TARGET_PC
FE10_PROTO p32ret fn_80030CF4(Un*);
#else
int fn_80030CF4(Un*);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_80118C44(p32arg);
#else
int fn_80118C44(int);
#endif
int* fn_80030CB4(Un*);
#pragma use_lmw_stmw on
static inline void Setup(Bat* b, int i, int k, Un* u) {
        if (u == NULL) {
            b->m54[i] = NULL;
            b->m5c[i] = NULL;
            return;
        }
        G5x* g = fn_800C22B0(i, b);
        b->m5c[i] = g;
        g->m48 = u;
        b->m5c[i]->m4c = fn_8002C84C(&lbl_803C8E80, k);
        b->m5c[i]->m38 = u->f4->m8;
        UP* q = fn_801D0784(b->m88, k);
        g = b->m5c[i];
        s16 hp = q->m6;
        g->m52 = hp;
        g->m50 = hp;
        g->m58 = 0;
        g->m54 = 0;
        b->m5c[i]->m5c = fn_801D0784(b->m88, k)->mC;
        b->m5c[i]->m60 = fn_80030CF4(u);
        if (lbl_803C8E80.flags & 0xC00000) {
            if (i == 1) b->m5c[i]->m39 = 1;
        } else {
            G3* h = fn_800C3300(i, b);
            b->m54[i] = h;
            h->m38 = u->f4->m8;
            b->m54[i]->m3c = fn_80118C44(u->ec);
        }
        b->m64->m34[i] = u;
        b->m64->m3c[i] = fn_8002C84C(&lbl_803C8E80, k);
        if (*fn_80030CB4(u) != 0) {
            b->m64->m3e[i] = fn_801D0784(b->m88, k)->m10;
            b->m64->m46[i] = fn_801D0784(b->m88, k)->m14;
            b->m64->m4a[i] = fn_801D0784(b->m88, k)->m16;
        }
        b->m64->m42[i] = fn_801D0784(b->m88, k)->m12;
}
void fn_800AB734(Bat* b) {
    b->m64 = NULL;
    b->m54[0] = NULL;
    b->m5c[0] = NULL;
    b->m54[1] = NULL;
    b->m5c[1] = NULL;
    if (b->m83 == 0) return;
    b->m64 = fn_800C2DFC(b);
    if (lbl_803C8E80.flags & 0xC00000) b->m64->m33 = 1;
    int i;
    int k;
    for (i = 0; i < 2; i++) {
        k = fn_801D0674(b->m88, i);
        Setup(b, i, k, (Un*)fn_801D0784(b->m88, k)->u);
    }
}
}
