#include "game/rG_800A3D88/chr.h"
extern "C" {
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
#if TARGET_PC
FE10_PROTO void* fn_800A8324(char*);
#else
void fn_800A8324(char*);
#endif
extern char lbl_80365064[];
struct A5 { u8 p[0x6D]; u8 m6d; u8 m6e; u8 p6f[7]; s8 m76; };
void
#if TARGET_PC
*
#endif
fn_800A5DE8(A5* a) {
    char buf[0x40];
    buf[0] = 0;
    switch (a->m76) {
    case 0: strcpy(buf, lbl_80365064 + 0xEE); break;
    case 1: strcpy(buf, lbl_80365064 + 0xFF); break;
    case 2: strcpy(buf, lbl_80365064 + 0x110); break;
    case 3: strcpy(buf, lbl_80365064 + 0x11F); break;
    case 4: strcpy(buf, lbl_80365064 + 0x12E); break;
    }
    if (a->m6d) fn_80291110(buf, lbl_80365064 + 0x13B);
    if (a->m6e) fn_80291110(buf, lbl_80365064 + 0x140);
#if TARGET_PC
    return fn_800A8324(buf);
#else
    fn_800A8324(buf);
#endif
}
struct B44 { u8 p[1]; };
struct EffE;
struct Unit { u8 p[0xF4]; struct { u8 p[8]; u8 m8; }* f4; };
struct UP { Unit* u; };
struct Bat {
    u8 p[0x3C];
    Chr* e[2];
    void* m44;
    u8 p48[0x70 - 0x48];
    Chr* m70;
    Chr* m74;
    s8 p78; u8 p79[5];
    s16 m7e;
    u8 m80; u8 m81; u8 p82[3]; u8 m85;
    void* m88;
};
extern char lbl_80365488[];
int fn_80194524(void*);
f32 fn_800A84A4(const char*);
int fn_800BD280(Chr*);
int fn_801D0674(void*, int);
UP* fn_801D0784(void*, int);
int fn_801D038C(void*);
Chr* fn_800A471C(void*);
void fn_800A4B00(void*, Chr*);
void fn_800A6100(void*, Chr*, const char*);
static inline Chr* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
static inline Chr* Pick(Bat* b) {
    for (int i = 0; i < 2; i++) {
        Chr* c = At(b, i);
        if (fn_800BD280(c)) {
            UP* up = fn_801D0784(b->m88, fn_801D0674(b->m88, i));
            if (up->u->f4->m8 == 0) return c;
        }
    }
    return NULL;
}
void fn_800AE368(Bat* b) {
    if (fn_80194524(b) != 0) {
    Chr* c = Pick(b);
    if (fn_801D038C(b->m88) < 0 && fn_800A471C(b->m44) != c) {
        fn_800A4B00(b->m44, c);
        fn_800A6100(b->m44, c, lbl_80365488 + 0x49);
    }
    b->m7e = fn_800A84A4(lbl_80365488 + 0x150);
    } else {
        b->m7e = fn_800A84A4(lbl_80365488 + 0x15F);
    }
}
struct FA { u8 p[0x18]; int m18; };
FA* fn_80007F10(Mdl*);
int fn_800B5D14(Chr*);
int fn_800ACF58(Bat* b) {
    UP* up = fn_801D0784(b->m88, fn_801D038C(b->m88));
    Unit* u = up->u != NULL ? *(Unit**)((u8*)up->u + 0x3F0) : NULL;
    Mdl* m = b->m74->mdl;
    FA* a = fn_80007F10(m);
    int t = a->m18 - (int)fn_800A84A4(lbl_80365488 + 0x120);
    if (!(b->m74->flags & 0x400000))
    switch (u->f4->m8) {
    case 0:
        if (!fn_800B5D14(b->m74)) return 1;
        break;
    default:
        if (m->frame > t) break;
        return 1;
    }
    return 0;
}
int fn_800A8208(const char*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(ChrData*, const char*);
#else
void* fn_800A7460(ChrData*, const char*);
#endif
int fn_800B1B48(Chr*, int, int, u16, int);
int fn_800B26B0(Chr*, const char*, int, u16);
void fn_800A5F08(void*, Chr*, int);
void fn_800BD024(Chr*, const char*);
void fn_800AC418(Bat* b) {
    Chr* c = NULL;
    if (b->m85 == 0) c = b->m70;
    if (b->m85 == 1) c = b->m74;
    if (c != NULL) {
        int k = fn_800A8208(lbl_80365488 + 0x4E);
        if (fn_800A7460(c->data, lbl_80365488 + 0x1D) != NULL && fn_800B1B48(c, k, 0, 0xFFFF, -1) != 0) {
            fn_800A4B00(b->m44, c);
            fn_800A5F08(b->m44, c, k);
            fn_800BD024(c, lbl_80365488 + 0x49);
        } else {
            fn_800B26B0(c, lbl_80365488 + 0x49, -1, 0xFFFF);
        }
    }
    b->m85++;
}
int fn_800B69D8(Chr*, int);
f32 fn_800B4240(Chr*, int);
void fn_800AC52C(Bat* b) {
    int k = fn_800A8208(lbl_80365488 + 0xCE);
    if (b->m81 != 0) {
        b->m80 = 1;
        fn_800B1B48(b->m70, k, -1, 0xFFFF, -1);
        b->m81 = 0;
    } else if (fn_800B69D8(b->m70, *(s8*)((u8*)b + 0x68)) == 0) {
        f32 d = fn_800B4240(b->m70, 1);
        if (d < fn_800A84A4(lbl_80365488 + 0xD3)) return;
        if (fn_800B1B48(b->m70, k, -1, 0xFFFF, -1) != 0) {
            b->m80 = 1;
            b->m70->flags |= 0x80000;
            if (d > fn_800A84A4(lbl_80365488 + 0xE0)) {
                fn_800A4B00(b->m44, b->m70);
                fn_800A5F08(b->m44, b->m70, k);
            }
        }
    }
}
}
