#include "game/rG_800A3D88/types.h"
extern "C" {
struct FR { u8 p[0x20]; u16 m20; u8 p22[2]; u8 m24; u8 m25; };
struct FaceD { void** m0; };
struct Fc {
    u8 p[0x30];
    void* m30;
    FR* m34;
    f32 m38, m3c;
    u8 m40; u8 m41; u8 m42; s8 m43;
    u8 p44[4];
    u32 m48;
    void* m4c;
    void* m50;
};
struct Ey { s16 a, b; };
struct Fp { u8 p[0x30]; Fc* m30; u8 p34[8]; Ey e[2]; };
extern const f32 lbl_804CD588, lbl_804CD564;
void fn_800C5A34(f32, Fc*, int, int, int, int, int, int);
void fn_800C6634(Fp* f, int w, int k) {
    Ey* e = w == 0 ? &f->e[0] : &f->e[1];
    switch (k) {
    case 0: e->b--; break;
    case 1:
        if (e->b < 2) e->b++;
        else if (e->b > 2) e->b--;
        break;
    case 2: e->b++; break;
    }
    if (e->b < 0) e->b = 0;
    if (e->b > 5) e->b = 5;
    switch (e->b) {
    case 0: e->a = 0; break;
    case 1: case 2: e->a = 1; break;
    case 3: case 4: case 5: e->a = 2; break;
    }
    Fc* c = f->m30;
    u32 fl = c->m48;
    f32 v = (f32)c->m34->m25 / lbl_804CD588;
    if (fl & 0x80) v += (f32)c->m40;
    if (fl & 0x20000) v -= lbl_804CD564;
    if (fl & 0x40000) v += lbl_804CD564;
    Ey* e2 = w == 0 ? &f->e[0] : &f->e[1];
    fn_800C5A34(v, c, (int)c->m38, (int)c->m3c, c->m42, w, e2->a, 1);
}
extern Fc* lbl_803E50D0[8];
extern u8 lbl_803827A8[];
extern char lbl_80365E0C[];
#if TARGET_PC
FE10_PROTO Fc* fn_80081050(void*, p32arg);
#else
Fc* fn_80081050(void*, int);
#endif
FR* fn_80076F54(const char*);
#if TARGET_PC
FE10_PROTO char * fn_80291480(const char*, const char*);
#else
int fn_80291480(const char*, const char*);
#endif
void* fn_800C79A0(void*);
static inline FR* FontGet(const char* name) {
    FR* r = fn_80076F54(name);
    if (r != NULL) return r;
    return fn_80076F54(lbl_80365E0C + 0x3A);
}
#pragma use_lmw_stmw on
Fc* fn_800C6210(const char* name, u32 fl) {
    char* base;
    int off;
    int s;
    int i;
    FR* r;
    Fc* f;

    for (i = 0; i < 8; i++) {
        if (lbl_803E50D0[i] == NULL) { s = i; break; }
    }
    if (i == 8) return NULL;
    base = (char*)lbl_803E50D0;
    off = s * 4;
    if (*(Fc**)(base + off) != NULL) return NULL;
    f = fn_80081050(lbl_803827A8, 3);
    r = FontGet(name);
    f->m34 = r;
    f->m40 = s;
    f->m41 = -1;
    f->m42 = 0;
    f->m48 = (fl | 0x400) & ~0xC00;
    if (r->m24 == 0) f->m48 |= 0x800;
    f->m43 = -1;
    if (fn_80291480(name, lbl_80365E0C + 0x44)) f->m48 |= 0x1000;
    *(Fc**)(base + off) = f;
    f->m30 = fn_800C79A0(*(void**)f->m34);
    return f;
}
extern u8 lbl_803827C0[], lbl_803827F8[], lbl_80382814[];
void* fn_80081050b(void*, void*);
#pragma use_lmw_stmw off
#pragma use_lmw_stmw on
struct Fx4 { u8 p[0x30]; void* m30; };

}
