#include "game/rG_800A3D88/chr.h"
extern "C" {
struct Sc { u8 m0; u8 m1; s16 m2; u8 p4[4]; u8 m8, m9; };
struct Ch { u8 pad[0x30]; Mdl* mdl; u8 p34[0x50-0x34]; u32 m50; u8 p54; s8 m55; u8 m56; };
struct Bat {
    u8 p[0x34];
    void* m34;
    u8 p38[4];
    Ch* e[2];
    void* m44;
    u8 p48[0x70 - 0x48];
    Ch* m70;
    Ch* m74;
    u8 p78[4];
    u16 m7c;
    s16 m7e;
    u8 m80; u8 m81; u8 p82[3]; u8 m85;
    Sc* m88;
};
#define SceneGlobal SceneGlobalX
struct SceneGlobal { u8 p[0x15EC]; u32 flags; };
extern SceneGlobal lbl_803C8E80;
extern char lbl_80365488[];
#define STR(n) (lbl_80365488 + (n))
int fn_800BD280(Ch*);
void* fn_801D0784(Sc*, int);
int fn_801CE540(void*);
int fn_800B26B0(Ch*, const char*, int, u16);
void fn_800BD024(Ch*, const char*);
#if TARGET_PC
FE10_PROTO void * fn_800B196C(Ch*, const char*);
#else
int fn_800B196C(Ch*, const char*);
#endif
void* fn_800A5DE8(void*);
int fn_800A4420(void*, void*, int);
f32 fn_800A84A4(const char*);
static inline Ch* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
#pragma use_lmw_stmw on
void fn_800ABAE4(Bat* b) {
    for (int i = 0; i < 2; i++) {
        Ch* c = At(b, i);
        if (fn_800BD280(c)) {
            if (fn_801CE540(fn_801D0784(b->m88, c->m55))) {
                if (fn_800B196C(c, STR(0x40))) fn_800B26B0(c, STR(0x40), -1, 0xFFFF);
                else fn_800B26B0(c, STR(0x49), -1, 0xFFFF);
            } else {
                if (fn_800B26B0(c, STR(0x4E), 0, 0xFFFF)) fn_800BD024(c, STR(0x49));
                else fn_800B26B0(c, STR(0x49), -1, 0xFFFF);
            }
        }
    }
    fn_800A4420(b->m44, fn_800A5DE8(b->m44), -1);
    b->m7e = fn_800A84A4(STR(0x57));
}
int fn_801D038C(Sc*);
int fn_801D040C(Sc*);
int fn_801D035C(Sc*);
int fn_801D0374(Sc*);
void fn_801CEAD0(Sc*);
int fn_801CEAE0(Sc*);
Ch* fn_800A93B8(Bat*, int);
void fn_80083DC4(void*, int);
void* fn_800B7468(Ch*);
void fn_800AEE68(void*, void*);
void fn_800AA2BC(Bat*, Ch*);
void fn_800ABC3C(Bat* b) {
    fn_801CEAD0(b->m88);
    if (fn_801CEAE0(b->m88)) {
        b->m70 = fn_800A93B8(b, fn_801D035C(b->m88));
        b->m74 = fn_800A93B8(b, fn_801D0374(b->m88));
        switch (b->m88->m1) {
        case 2: case 3:
            { void* a = b->m34; fn_800AEE68(a, fn_800B7468(b->m70)); }
            break;
        }
        fn_800AA2BC(b, b->m70);
    } else {
        b->m70 = fn_800A93B8(b, fn_801D038C(b->m88));
        b->m74 = fn_800A93B8(b, fn_801D040C(b->m88));
        fn_80083DC4(b, 7);
    }
    for (int i = 0; i < 2; i++) {
        Ch* c = At(b, i);
        if (fn_800BD280(c)) c->m50 &= ~0x800;
    }
}
void fn_800A9E64(Bat*, int, int);
void fn_800A9FC8(Bat*, int, int);
void fn_800AA1E4(Bat*, int);
int fn_800BD22C(Ch*);
void fn_800ABE64(Bat* b) {
    Sc* s = b->m88;
    if (s->m9 != 0) {
        fn_801CEAE0(s);
        fn_80083DC4(b, 5);
        return;
    }
    if (s->m2 == 0x70) b->m7e = fn_800A84A4(STR(0x66));
    else b->m7e = fn_800A84A4(STR(0x75));
    fn_800A9E64(b, 100, -1);
    fn_800A9FC8(b, 100, -1);
    fn_800AA1E4(b, 0);
    if (b->m88->m8 != 0) {
        if (lbl_803C8E80.flags & 0x200000) {
            b->m7c = 3000;
            fn_80083DC4(b, 0xC);
            return;
        }
        if (fn_800BD22C(b->m70)) goto L;
    }
    fn_800B26B0(b->m70, STR(0x49), -1, 0xFFFF);
    b->m70->m56 = 0;
L:
    fn_80083DC4(b, 4);
}
int fn_800A8208(const char*);
int fn_800B1B48(Ch*, int, int, u16, int);
Vec fn_800B5C3C(Ch*);
void fn_800B2944(Ch*, f32, f32, f32);
void fn_800A4B00(void*, Ch*);
void fn_800A5F08(void*, Ch*, int);
static inline void SetPos(Ch* c, Vec v) { fn_800B2944(c, v.x, v.y, v.z); }
void fn_800AC284(Bat* b) {
    for (int i = 0; i < 2; i++) {
        Ch* c = At(b, i);
        if (fn_800BD280(c)) {
            if (fn_801CE540(fn_801D0784(b->m88, c->m55)) != 0 && fn_800B196C(c, STR(0x40)) != 0) fn_800B26B0(c, STR(0x40), -1, 0xFFFF);
            else fn_800B26B0(c, STR(0x49), -1, 0xFFFF);
        }
    }
    int k = fn_800A8208(STR(0x3B));
    if (fn_800B1B48(b->m70, k, 0, 0xFFFF, -1)) {
        Vec p = fn_800B5C3C(b->m70);
        SetPos(b->m70, p);
        b->m70->m50 |= 0x80000;
        fn_800A4B00(b->m44, b->m70);
        fn_800A5F08(b->m44, b->m70, k);
        fn_800AA2BC(b, b->m70);
    }
}
}
