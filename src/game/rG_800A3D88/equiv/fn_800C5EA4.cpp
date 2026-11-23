/* fn_800C5EA4: functionally equal (renamed, 26 of 157 words differ in registers only). Helpers from fn_800C6210.cpp (exported bodies removed), body from wip/fn_800C6210.cpp plus the missing f->m30 = NULL at the end of the second branch and a separate return in the first. */
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
void fn_800C6634(Fp* f, int w, int k);

extern Fc* lbl_803E50D0[8];
extern u8 lbl_803827A8[];
extern char lbl_80365E0C[];
Fc* fn_80081050(void*, int);
FR* fn_80076F54(const char*);
int fn_80291480(const char*, const char*);
void* fn_800C79A0(void*);
static inline FR* FontGet(const char* name) {
    FR* r = fn_80076F54(name);
    if (r != NULL) return r;
    return fn_80076F54(lbl_80365E0C + 0x3A);
}
#pragma use_lmw_stmw on

Fc* fn_800C6210(const char* name, u32 fl);

extern u8 lbl_803827C0[], lbl_803827F8[], lbl_80382814[];
void* fn_80081050b(void*, void*);
#pragma use_lmw_stmw off
#pragma use_lmw_stmw on
struct Fx4 { u8 p[0x30]; void* m30; };

}

/* ---- from rG_800A3D88/wip/fn_800C6210.cpp ---- */
extern "C" {
// Near misses, see NOTES.md. Needs declarations from ../fn_800C6210.cpp.
Fc* fn_800C5EA4(int i, const char* name, int x, int y, u32 fl, int z, int par) {
/*P*/
    Fc* f;
    FR* r;
/*E*/
    r = FontGet(name);
    if (lbl_803E50D0[i] != NULL) return NULL;
    if (fl & 0x100) {
        if (par == 0) par = 3;
        f = fn_80081050(lbl_803827A8, par);
        f->m34 = r;
        f->m40 = i;
        f->m38 = x;
        f->m3c = y;
        f->m48 = fl;
        f->m41 = -1;
        f->m42 = 0;
        if (fl & 0x400) {
            f->m48 &= ~0xC00;
            if (f->m34->m24 == 0) f->m48 |= 0x800;
        }
        f->m4c = NULL;
        f->m50 = NULL;
        lbl_803E50D0[i] = f;
        f->m30 = NULL;
        return f;
    } else {
        if (par == 0) par = 3;
        f = fn_80081050(lbl_803827C0, par);
        f->m34 = r;
        f->m40 = i;
        f->m38 = x;
        f->m3c = y;
        f->m48 = fl;
        f->m41 = -1;
        f->m42 = 0;
        if (fl & 0x400) {
            f->m48 &= ~0xC00;
            if (f->m34->m24 == 0) f->m48 |= 0x800;
        }
        f->m4c = NULL;
        f->m50 = NULL;
        lbl_803E50D0[i] = f;
        if (fn_80291480(name, lbl_80365E0C + 0x44)) f->m48 |= 0x1000;
        if (!(fl & 0x200)) {
            if (r->m20 & 2) f->m4c = fn_80081050(lbl_803827F8, (int)f);
            if (r->m20 & 1) f->m50 = fn_80081050(lbl_80382814, (int)f);
        }
        f->m30 = NULL;
    }
    return f;
}
}
