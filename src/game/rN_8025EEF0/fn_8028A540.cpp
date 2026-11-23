/* GX state for the framebuffer capture quad */
#include "game/rN_8025EEF0/calls.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

void fn_80308090(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_80312F48(void* m, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_80307D98(void* m, int a);
void fn_80312318(void* m);
void fn_80307E48(void* m, int a);
void fn_80021784(int a);
void fn_803031CC(void);
void fn_80302B80(int a, int b);
void fn_80303200(int a, int b, int c, int d, int e);
void fn_80022254(void* p, int a);
void fn_80021CB4(int a, int b, int c, int d);
void fn_80021BF4(int a);
void fn_80021E20(int a, int b, int c, int d, int e);
void fn_80021D18(int a, int b, int c, int d, int e, int f);
void fn_80021E8C(int a, int b, int c, int d, int e);
void fn_80021D9C(int a, int b, int c, int d, int e, int f);
void fn_80021C34(int a);
void fn_80021F7C(int a, int b, int c, int d);
void fn_80021B2C(int a);
void fn_80021A08(int a, int b, int c, int d, int e, int f, int g);
void fn_800218A8(int a, C4 c);
void fn_80021958(int a, C4 c);
void fn_80021C74(int a);
void fn_80306B24(int a);
void fn_80022158(int a, int b, int c);
void fn_80306FD8(int a, int b, int c, int d, int e);
void fn_80021BA4(int a, int b, int c, int d);
void fn_80021860(int a, int b, int c);
void fn_80021808(int a, int b, int c, int d, int e);

void fn_8028A540(void* tex) {
    u8 m2[0x40];
    u8 m1[0x30];
    C4 ca = {0xFF, 0xFF, 0xFF, 0xFF};
    C4 cb = {0, 0, 0, 0xFF};
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    fn_80312F48(m2, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
    fn_80307D98(m2, 1);
    fn_80312318(m1);
    fn_80307E48(m1, 0x1B);
    fn_80021784(0x1B);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(7, 9, 0, 3, 0);
    fn_80303200(7, 0xD, 1, 3, 0);
    fn_80022254(tex, 0);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021BF4(1);
    fn_80021E20(0, 0xF, 10, 8, 0xF);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 7, 7, 5);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_800218A8(4, cb);
    fn_80021958(4, ca);
    fn_80021C74(0);
    fn_80306B24(0);
    fn_80022158(0, 0, 0);
    fn_80306FD8(0, 0, 1, 2, 3);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(1, 3, 0);
    fn_80021808(7, 0, 0, 7, 0);
}

}
