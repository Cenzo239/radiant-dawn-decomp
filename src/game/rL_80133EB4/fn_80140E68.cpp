#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Tex { u8 p[0x20]; };
struct Color { u8 r, g, b, a; };
struct Wk { u8 pad[0x3C]; void* x3c; };
struct MM {
    u8 pad0[0x14];
    Wk* x14;
    u8 pad18[0x57 - 0x18];
    u8 x57;
    u8 pad58[0x5C - 0x58];
    f32 x5c;
    u8 pad60[0xD0 - 0x60];
    f32 scale;
    Vec xd4;
    u8 pade0[4];
    u8 xe4[0x30];
};
#define FIFO (*(volatile f32*)0xCC008000)
extern "C" {
static const Color sC1 = {0, 0, 0, 0xFF};
static const Color sC2 = {0, 0xFF, 0, 0xFF};
extern u8 lbl_80413D50[];
extern MM* fn_8013B9A8(void);
extern void* fn_8000F470(void);
extern int fn_80140C8C(void*, Mtx*, f32);
extern void fn_8000F7F4(void*, void*);
extern void fn_8000F468(void*);
extern void fn_8000F9C8(void*, int, int, int, int);
extern void fn_8000F9E8(void*, f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_800100C8(p32arg);
#else
extern void fn_800100C8(int);
#endif
extern void fn_80312378(void*, void*, void*);
extern void fn_8000FA30(void*);
extern void fn_80011274(void);
extern u32* fn_8013B260(MM*, int);
extern void fn_8001A4DC(void*);
extern void fn_8013B288(MM*, u32);
extern void fn_80134ECC(MM*, u32, u32);
extern void fn_803047B0(int, int, int, int);
extern void fn_80304814(int, int, int, int);
extern void fn_80305020(void*, int);
extern void fn_8001E6D0(void*, void*);
extern void* fn_8000FB88(void);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_80021B2C(int);
extern void fn_800218A8(int, Color*);
extern void fn_80021958(int, Color*);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80022254(void*, int);
extern void fn_8000FEA0(void*, void*);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021860(int, int, int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80304314(int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(p32arg);
#else
extern void fn_800104DC(int);
#endif
extern void fn_80011838(int);
extern void fn_80303D74(void);
extern void fn_803061BC(void);

void fn_80140E68(void) {
    Wk* w;
    MM* mm = fn_8013B9A8();
    if (mm == 0) return;
    w = mm->x14;
    if (w == 0) return;
    if (mm->x57 == 0) return;
    Mtx md;
    Mtx ma;
    Mtx m7;
    Mtx m4;
    Tex tex;
    Vec v = mm->xd4;
    f32 h = mm->x5c * (5.0f * mm->scale);
    h += v.y;
    void* cam = fn_8000F470();
    u8* q = lbl_80413D50;
    fn_80140C8C(cam, &md, h);
    fn_8000F7F4(cam, q);
    fn_8000F468(q);
    fn_8000F9C8(q, 0, 0, 0x130, 0x1C0);
    fn_8000F9E8(q, 0.0f, 0.0f, 304.0f, 448.0f);
    fn_800100C8(0);
    fn_80312378(q + 0xA4, &md, q + 0xA4);
    fn_8000FA30(q);
    fn_80011274();
    u32* p = fn_8013B260(mm, 0);
    if (p) {
        u32 f = *p;
        *p = (f ^ 0x8000000) | 0x8000;
        fn_8001A4DC(p);
        *p = f;
    }
    fn_8013B288(mm, 0x8000000);
    fn_80134ECC(mm, 0x40, 0);
    fn_80134ECC(mm, 0x8000000, 0xC0);
    fn_8013B288(mm, 0x8000000);
    fn_803047B0(0, 0, 0x130, 0x1C0);
    fn_80304814(0x130, 0x1C0, 4, 0);
    fn_80305020(w->x3c, 0);
    for (int i = 1; i < 8; i++) {
        u32* p2 = fn_8013B260(mm, i);
        if (p2) {
            u32 f = *p2;
            *p2 = (f ^ 0x8000000) | 0x8000;
            fn_8001A4DC(p2);
            *p2 = f;
        }
    }
    fn_8001E6D0(mm->xe4, &m4);
    fn_80312378(fn_8000FB88(), &m4, &m4);
    fn_80307E48(&m4, 0);
    fn_80021784(0);
    fn_80021B2C(1);
    {
        Color c = sC1;
        fn_800218A8(4, &c);
    }
    {
        Color c = sC2;
        fn_80021958(4, &c);
    }
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021EF8(0, 4);
    fn_80305A40(&tex, w->x3c, 0x130, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(&tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    fn_80022254(&tex, 0);
    fn_8001E6D0(mm->xe4, &ma);
    fn_8000FEA0(q, &m7);
    fn_80312378(&m7, &ma, &m4);
    fn_80307F10(&m4, 0x1E, 0);
    fn_80021F7C(0, 0, 0, 0x1E);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021EF8(0, 3);
    fn_80021C34(1);
    fn_80021860(1, 4, 1);
    fn_80021808(0, 0, 1, 7, 0);
    fn_80021BA4(0, 1, 1, 0);
    fn_80021B68(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80303200(0, 9, 1, 4, 0);
    {
        f32 k = 64.0f * (5.0f * mm->scale);
        fn_80304314(0x98, 0, 4);
        f32 n = -k;
        FIFO = n;
        FIFO = h;
        FIFO = n;
        FIFO = k;
        FIFO = h;
        FIFO = n;
        FIFO = n;
        FIFO = h;
        FIFO = k;
        FIFO = k;
        FIFO = h;
        FIFO = k;
    }
    fn_800104DC(0);
    fn_8000F468(cam);
    fn_80011274();
    fn_80011838(-1);
    fn_803047B0(0, 0, 0x130, 0x1C0);
    fn_80304814(0x130, 0x1C0, 4, 0);
    fn_80305020(w->x3c, 1);
    fn_80303D74();
    fn_803061BC();
}
}
