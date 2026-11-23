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
#if TARGET_PC
FE10_PROTO extern char *lbl_804CA5A0, *lbl_804CA5AC;
#else
extern char lbl_804CA5A0[12], lbl_804CA5AC[12];
#endif
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
FE10_PROTO struct Entry24 * fn_800A8008(const char*);
FE10_PROTO int fn_800A67EC(p32arg);
#else
int fn_800A8008(const char*);
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
static inline int IsR(Bat* b) { if (b->m78 < 4 && b->m78 >= 2) return 1; return 0; }
#pragma use_lmw_stmw on

int fn_801CFA90(Sc*);
int fn_800B75FC(Ch*, Sc*);
int fn_800B727C(Ch*, const char*);
u32 fn_80089ED0();
int fn_801CFCE0(Sc*);
int fn_800B6E2C(Ch*, int, int);
void fn_800BCC5C(Ch*, int);
void fn_800ABFB8(Bat* b) {
    b->m68 = -1;
    b->m69 = -1;
    b->m84 = 0;
    if (fn_801CFA90(b->m88)) {
        switch (b->m88->mB) {
        case 1: b->m68 = fn_800B727C(b->m70, STR(0x84)); break;
        case 2: b->m68 = fn_800B727C(b->m70, STR(0x8B)); break;
        case 3: b->m68 = fn_800B727C(b->m70, STR(0x92)); break;
        case 4: b->m68 = fn_800B727C(b->m70, STR(0x99)); break;
        case 5: b->m68 = fn_800B727C(b->m70, STR(0xA0)); break;
        }
    } else {
        b->m68 = fn_800B75FC(b->m70, b->m88);
    }
    if ((lbl_803C8E80.flags & 0x200000) && b->m88->m8 != 0) {
        b->m68 = fn_800B727C(b->m70, STR(0));
    }
    switch (b->m88->m2) {
    case 0x6E: case 0x6F:
        if (fn_801CFCE0(b->m88)) {
            b->m69 = fn_800B727C(b->m74, STR(0xA7));
            b->m84 = 1;
        } else {
            b->m69 = fn_800B727C(b->m74, STR(0xAE));
        }
        break;
    case 0x70:
        if (fn_80089ED0() & 1) b->m69 = fn_800B727C(b->m74, STR(0xB7));
        if (b->m69 < 0) b->m69 = fn_800B727C(b->m74, STR(0xBE));
        if (fn_800A7460(b->m74->data, STR(0xC5))) b->m84 = 1;
        break;
    }
    b->m80 = 0;
    b->m6b = 0;
    b->m6c = 0;
    b->m6a = 0;
    b->m6a += fn_800B6E2C(b->m70, b->m68, 0);
    if (b->m6a == 0) {
        b->m6a += fn_800B6E2C(b->m70, b->m68, 2);
        b->m6a += fn_800B6E2C(b->m70, b->m68, 0x12);
    }
    fn_800BCC5C(b->m70, b->m68);
    fn_800BCC5C(b->m74, b->m69);
}
void fn_800BB074(Ch*, Sc*);
void fn_800B5010(Ch*);
void fn_800A4BDC(void*, int);
int fn_800B79AC(Ch*);
int fn_800B1B48(Ch*, int, int, u16, int);
void fn_800BD024(Ch*, const char*);
int fn_801CFE78(Sc*, u16);
void fn_800AADBC(Bat*, u16);
void fn_800B38F0(Vec*, Ch*, int);
void fn_800B377C(Vec*, Ch*, int);
void fn_800EE1BC(Vec*, Bat*);
void fn_800EDE14(Vec*, Bat*);
void fn_800BCF10(Ch*);
void fn_802549C4(const char*, Vec*, f32);
extern const f32 lbl_804CD358;
struct W3 { u32 a, b, c; };
void fn_800AD740(Bat* b, Ch* a, Ch* d) {
    Vec v1; Vec t1; Vec v2; Vec t2; Vec v3; Vec t3;
    b->m6b++;
    fn_800BB074(a, b->m88);
    fn_800B5010(a);
    fn_800A4BDC(b->m44, 0x6D);
    if (fn_800B1B48(a, fn_800B79AC(a), -1, 0xFFFF, -1)) {
        fn_800BD024(a, STR(0x49));
        b->m6b = b->m6a;
    }
    if (fn_800B1B48(d, b->m69, -1, 0xFFFF, -1)) fn_800BD024(d, STR(0x49));
    if (b->m6b == b->m6a) {
        int i; u16 k; int off;
        for (i = 0, off = 0; i < b->m88->mC; off += 2, i++) {
            k = *(u16*)((u8*)b->m88 + off + 0xE);
            if (fn_801CFE78(b->m88, k)) fn_800AADBC(b, k);
        }
        if (b->m83 != 0) {
            if (b->m88->m2 == 0x70) {
                fn_800B38F0(&t1, d, -1);
                *(W3*)&v1 = *(W3*)&t1;
                fn_800EE1BC(&v1, b);
            } else {
                fn_800B38F0(&t2, d, -1);
                *(W3*)&v2 = *(W3*)&t2;
                fn_800EDE14(&v2, b);
            }
        }
    }
    fn_800BCF10(d);
    fn_800B377C(&t3, d, -1);
    v3 = t3;
    fn_802549C4(STR(0x21A), &v3, lbl_804CD358);
}
}
