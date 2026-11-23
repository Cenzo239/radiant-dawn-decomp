/* GX screen effects: quads through the write-gather pipe. */
#include "game/rR_80175E5C/types.h"
#define FIFOF (*(volatile f32*)0xCC008000)
#define FIFOB (*(volatile u8*)0xCC008000)

extern "C" {
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021C34(int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(int);
void fn_80021CB4(int, int, int, int);
void fn_80021EF8(int, int);
void fn_80021860(int, int, int);
void fn_80021B68(int);
void fn_80021BA4(int, int, int, int);
void fn_80304314(int, int, int);
void fn_80011838(int);
void* fn_802356AC();
void fn_80304CEC(int, void*, int, void*);
void fn_803047B0(u16, u16, u16, u16);
void fn_80304814(u16, u16, int, int);
void fn_80305020(void*, int);
void fn_80303D74();
void fn_803061BC();
#if TARGET_PC
FE10_PROTO void fn_80020764(int, int, int, int, p32arg);
#else
void fn_80020764(int, int, int, int, int);
#endif
void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
void fn_80305C94(void*, int, int, f32, f32, f32, int, int, int);
void fn_80022254(void*, int);
void fn_80312318(void*);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80307F10(void*, int, int);
void fn_80021F7C(int, int, int, int);
void fn_80021808(int, int, int, int, int);

static inline void Pos(f32 x, f32 y, f32 z) {
    FIFOF = x;
    FIFOF = y;
    FIFOF = z;
}
static inline void Col(u8 r, u8 g, u8 b, u8 a) {
    FIFOB = r;
    FIFOB = g;
    FIFOB = b;
    FIFOB = a;
}
static inline void Tc(f32 s, f32 t) {
    FIFOF = s;
    FIFOF = t;
}

void fn_801762B4(int x, int y, int w, int h) {
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021C34(0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021EF8(0, 4);
    fn_80021860(0, 3, 0);
    fn_80021B68(0);
    fn_80021BA4(1, 0, 7, 0);
    fn_80304314(0x80, 0, 4);
    Pos(x, y, 0.0f);
    Col(0xFF, 0xFF, 0xFF, 0xFF);
    Pos(x + w, y, 0.0f);
    Col(0xFF, 0xFF, 0xFF, 0xFF);
    Pos(x + w, y + h, 0.0f);
    Col(0xFF, 0xFF, 0xFF, 0xFF);
    Pos(x, y + h, 0.0f);
    Col(0xFF, 0xFF, 0xFF, 0xFF);
    fn_80011838(-1);
}

#pragma use_lmw_stmw on
void fn_801764F8(int x, int y, int w, int h, void* p) {
    u8* m = (u8*)fn_802356AC();
    fn_80304CEC(0, m + 0x1A, 0, m + 0x32);
    fn_803047B0(x, y, w, h);
    fn_80304814(w, h, 0x27, 0);
    fn_80305020(p, 0);
    fn_80304CEC(m[0x19], m + 0x1A, 1, m + 0x32);
    fn_80303D74();
    fn_803061BC();
}
#pragma use_lmw_stmw off

void fn_8017659C(
#if TARGET_PC
f32 z, int x, int y, int w, int h, int tw, void* e, void* tex
#else
f32 z, int x, int y, int w, int h, int tw, int e, void* tex
#endif
) {
    u8 t[0x20];
    f32 m1[3][4];
    f32 m2[3][4];
    fn_80020764(x, y, w, h, e);
    fn_80305A40(t, tex, w, h, 0x11, 0, 0, 0);
    fn_80305C94(t, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    fn_80022254(t, 0);
    fn_80022254(t, 1);
    fn_80312318(m1);
    m1[0][3] = 0.5f * tw / w;
    fn_80312318(m2);
    m2[1][3] = 0.5f * tw / h;
    fn_80021C34(2);
    fn_80021BF4(2);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021E20(0, 0xF, 0xF, 0xF, 0xF);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 4, 7, 7, 7);
    fn_80021D9C(0, 0, 0, 0, 0, 0);
    fn_80021CB4(1, 1, 1, 0xFF);
    fn_80021E20(1, 0xF, 0xF, 0xF, 0);
    fn_80021D18(1, 0, 0, 0, 1, 0);
    fn_80021E8C(1, 4, 7, 7, 0);
    fn_80021D9C(1, 1, 0, 0, 0, 0);
    fn_80307F10(m1, 0x1E, 1);
    fn_80307F10(m2, 0x21, 1);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021F7C(0, 1, 4, 0x1E);
    fn_80021F7C(1, 1, 4, 0x21);
    fn_80021808(6, 1, 0, 3, 0xFF);
    fn_80021860(0, 3, 0);
    fn_80021BA4(1, 6, 7, 0);
    fn_80021B68(0);
    fn_80304314(0x80, 0, 4);
    Pos(x, y, z);
    Tc(0.0f, 0.0f);
    Pos(x + w, y, z);
    Tc(1.0f, 0.0f);
    Pos(x + w, y + h, z);
    Tc(1.0f, 1.0f);
    Pos(x, y + h, z);
    Tc(0.0f, 1.0f);
    fn_80011838(-1);
}
}
