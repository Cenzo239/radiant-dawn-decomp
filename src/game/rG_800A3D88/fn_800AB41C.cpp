#include "game/rG_800A3D88/chr.h"
extern "C" {
struct Sc { u8 m0; u8 m1; s16 m2; u8 p4[4]; u8 m8, m9; u8 pA; u8 mB; u8 mC; u8 pD; u16 mE[1]; };
struct Un { u8 p[0xEC]; int ec; u8 pf0[4]; struct { u8 p[8]; u8 m8; }* f4; };
struct UP { Un* u; u8 p4[2]; s16 m6; u8 p8[4]; s16 mC; u8 pe[2]; s16 m10, m12, m14, m16; };
struct Ch { u8 pad[0x30]; Mdl* mdl; u8 p34[0x50-0x34]; u32 m50; u8 p54; s8 m55; u8 m56; s8 m57; u8 p58[0x78-0x58]; void* data; };
struct Bat {
    u8 p[0x34];
    void* m34;
    u8 p38[4];
    Ch* e[2];
    void* m44;
    u8 p48[0x54 - 0x48];
    void* m54[2];
    void* m5c[2];
    struct Gg* m64;
    s8 m68, m69;
    u8 m6a, m6b, m6c;
    u8 p6d[3];
    Ch* m70;
    Ch* m74;
    s8 m78;
    u8 m79;
    s8 m7a;
    u8 p7b;
    u16 m7c;
    s16 m7e;
    u8 m80; u8 m81; u8 m82; u8 m83; u8 m84; u8 m85;
    Sc* m88;
    void* m8c[2];
    int m94;
};
#define SceneGlobal SceneGlobalX
struct SceneGlobal { u8 p[0x15EC]; u32 flags; void* m15f0[2]; };
extern SceneGlobal lbl_803C8E80;
extern char lbl_80365488[];
extern char* lbl_804CA5A0;
extern char* lbl_804CA5AC;
#define STR(n) (lbl_80365488 + (n))
int fn_800BD280(Ch*);
UP* fn_801D0784(Sc*, int);
int fn_801D0674(Sc*, int);
void* fn_800A75E8(Un*, int);
void fn_800B1120(Ch*);
void fn_800B1628(Ch*, Un*);
#if TARGET_PC
FE10_PROTO char ** fn_801CE474(UP*);
FE10_PROTO void fn_800B4574(Ch*, p32arg, int);
#else
int fn_801CE474(UP*);
void fn_800B4574(Ch*, int, int);
#endif
void fn_800B540C(Ch*, Un*);
void fn_800B54DC(Ch*, int);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(void*, const char*);
#else
void* fn_800A7460(void*, const char*);
#endif
int fn_8011B77C(void*, void*);
void fn_800BEBD4(Ch*);
#if TARGET_PC
FE10_PROTO p32ret fn_800A8008(const char*);
#else
int fn_800A8008(const char*);
#endif
#if TARGET_PC
FE10_PROTO int fn_800A67EC(p32arg);
#else
int fn_800A67EC(int);
#endif
void fn_800B4744(Ch*, int, int);
Ch* fn_800A93B8(Bat*, int);
int fn_801D035C(Sc*);
int fn_801D0374(Sc*);
#if TARGET_PC
FE10_PROTO void * fn_800B196C(Ch*, const char*);
#else
int fn_800B196C(Ch*, const char*);
#endif
static inline Ch* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
static inline Un* UnitOf(UP* p) { return p->u != NULL ? *(Un**)((u8*)p->u + 0x3F0) : NULL; }
static inline int IsR(Bat* b) { switch (b->m78) { case 2: case 3: return 1; default: return 0; } }
#pragma use_lmw_stmw on

static inline int MC(Sc* s) { return s->mC; }
struct UnX { u8 p[300]; u8 a[4]; };
int fn_800AB41C(Bat* b) {
Ch* c2;
UnX* u;
UP* p;
int i;
Ch* c;
Bat* qj;
int j;
Bat* q2;
Bat* q;
int i2;
    for (q = b, i = 0; i < 2; i++, q = (Bat*)((u8*)q + 4)) {
        if (i < 0) c = NULL; else c = q->e[0];
        int k = fn_801D0674(b->m88, i);
        c->m55 = k;
        p = fn_801D0784(b->m88, k);
        if (p != NULL && UnitOf(p) != NULL) {
            void* d;
            if (IsR(b)) d = fn_800A75E8(UnitOf(p), 1);
            else d = fn_800A75E8(UnitOf(p), 0);
            if (d == NULL) return 0;
            c->data = d;
            fn_800B1120(c);
            fn_800B1628(c, p->u);
            fn_800B4574(c, fn_801CE474(p), 0);
            for (qj = b, j = 0; j < 2; j++, qj = (Bat*)((u8*)qj + 4)) {
                if (lbl_803C8E80.m15f0[j != 0] != NULL) {
                    qj->m8c[0] = fn_800A75E8((Un*)lbl_803C8E80.m15f0[j != 0], 0);
                }
            }
        }
    }
    for (q2 = b, i2 = 0; i2 < 2; i2++, q2 = (Bat*)((u8*)q2 + 4)) {
        if (i2 < 0) c2 = NULL; else c2 = q2->e[0];
        if (fn_800BD280(c2)) {
            u = (UnX*)fn_801D0784(b->m88, c2->m55)->u;
            fn_800B540C(c2, (Un*)u);
            c2->m57 = b->m78;
            fn_800B54DC(c2, -1);
            if (fn_800A7460(c2->data, STR(0x1D)) != NULL) {
                b->m82 = 1;
                b->m85 = 0;
            }
            if (fn_8011B77C(u->a, lbl_804CA5A0)) fn_800BEBD4(c2);
            if (fn_8011B77C(u->a, lbl_804CA5AC)) {
                fn_800BEBD4(c2);
                int h = fn_800A8008(STR(0x2A));
                if (h) fn_800B4744(c2, fn_800A67EC(h), 0);
            }
        }
    }
    b->m70 = fn_800A93B8(b, fn_801D035C(b->m88));
    b->m74 = fn_800A93B8(b, fn_801D0374(b->m88));
    if (b->m81 != 0) {
        if (fn_800B196C(b->m70, STR(0x3B)) == 0) b->m81 = 0;
        if (b->m82 != 0) b->m81 = 0;
        if (MC(b->m88) > 0) b->m81 = 0;
    }
    return 1;
}
}
