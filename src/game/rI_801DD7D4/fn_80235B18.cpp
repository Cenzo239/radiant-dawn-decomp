#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off
extern "C" {
struct C2 { s16 a, b, c, d; };
struct C4 { u8 r,g,b,a; };
void fn_80312318(void*);
void fn_80307E48(void*, int);
void fn_80021784(int);
void fn_80021B2C(int);
void fn_80021A08(int,int,int,int,int,int,int);
void fn_80021C34(int);
void fn_80021F7C(int,int,int,int);
void fn_803031CC(void);
void fn_80302B80(int,int);
void fn_80303200(int,int,int,int,int);
void fn_80021BF4(int);
void fn_80021CB4(int,int,int,int);
void fn_80021E20(int,int,int,int,int);
void fn_80021D18(int,int,int,int,int,int);
void fn_80021E8C(int,int,int,int,int);
void fn_80021D9C(int,int,int,int,int,int);
void fn_80021FF0(int,int);
void fn_80022050(int,int);
void fn_80022158(int,int,int);
void fn_80306E3C(int, C2);
void fn_80306EA0(int, C4);
void fn_80306FD8(int,int,int,int,int);
static const C2 kA = {-90, 0, -114, 135};
static const C4 kB = {0, 0, 0xE2, 0x58};
static const C4 kC = {0xB3, 0, 0, 0xB6};
static const C4 kD = {0xFF, 0, 0xFF, 0x80};
void fn_80235B18(void) {
    u8 m[0x30];
    fn_80312318(m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80021B2C(0);
    fn_80021A08(4,0,1,1,0,0,2);
    fn_80021A08(5,0,1,1,0,0,2);
    fn_80021C34(2);
    fn_80021F7C(0,1,4,0x3c);
    fn_80021F7C(1,1,4,0x3c);
    fn_803031CC();
    fn_80302B80(9,1);
    fn_80302B80(0xd,1);
    fn_80303200(7,9,1,3,0);
    fn_80303200(7,0xd,1,2,0);
    fn_80021BF4(5);
    fn_80021CB4(0,1,1,0xff);
    fn_80021E20(0,0xf,8,0xe,2);
    fn_80021D18(0,0,0,0,0,0);
    fn_80021E8C(0,7,4,6,1);
    fn_80021D9C(0,1,0,0,0,0);
    fn_80021FF0(0,0xc);
    fn_80022050(0,0x1c);
    fn_80022158(0,0,0);
    fn_80021CB4(1,1,2,0xff);
    fn_80021E20(1,0xf,8,0xe,0);
    fn_80021D18(1,0,0,1,0,0);
    fn_80021E8C(1,7,4,6,0);
    fn_80021D9C(1,1,0,0,0,0);
    fn_80021FF0(1,0xd);
    fn_80022050(1,0x1d);
    fn_80022158(1,0,0);
    fn_80021CB4(2,0,0,0xff);
    fn_80021E20(2,0xf,8,0xc,0);
    fn_80021D18(2,0,0,0,1,0);
    fn_80021E8C(2,4,7,7,0);
    fn_80021D9C(2,0,0,0,1,0);
    fn_80022158(2,0,0);
    fn_80021CB4(3,0xff,0xff,0xff);
    fn_80021E20(3,1,0,0xe,0xf);
    fn_80021D18(3,0,0,0,1,0);
    fn_80021E8C(3,7,7,7,7);
    fn_80021D9C(3,0,0,0,1,0);
    fn_80022158(3,0,0);
    fn_80021FF0(3,0xe);
    fn_80021CB4(4,0xff,0xff,0xff);
    fn_80021E20(4,0xf,0,0xe,0xf);
    fn_80021D18(4,0,0,0,1,0);
    fn_80021E8C(4,6,7,7,7);
    fn_80021D9C(4,0,0,0,1,0);
    fn_80022158(4,0,0);
    fn_80021FF0(4,0xf);
    fn_80022050(4,0x1f);
    fn_80306E3C(1, kA);
    fn_80306EA0(0, kB);
    fn_80306EA0(1, kC);
    fn_80306EA0(2, kD);
    fn_80306FD8(0,0,1,2,3);
}
void DCInvalidateRange(void*, u32);
void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
void fn_80022254(void*, int);
void fn_80304314(int, int, int);
#define FF (*(volatile s16*)0xCC008000)
void fn_80235FF4(
#if TARGET_PC
void* y, void* u, void* v, s16 x0, s16 y0, s16 z0, fe10_rgba cv, s16 w, s16 h, s16 tw, s16 th
#else
void* y, void* u, void* v, s16 x0, s16 y0, s16 z0, const C4* c, s16 w, s16 h, s16 tw, s16 th
#endif
) {
#if TARGET_PC
    const C4* c = (const C4*)&cv;
#endif
    u8 ty[0x20], tu[0x20], tv[0x20];
    int wr; int h2; int w2; u8 same = 0;
    if (w == tw && h == th) same = 1;
    wr = same == 0;
    fn_80305A40(ty, y, w, h, 1, 0, 0, 0);
    fn_80305C94(ty, wr, wr, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    fn_80022254(ty, 0);
    h2 = h >> 1; w2 = w >> 1;
    fn_80305A40(tu, u, w2, h2, 1, 0, 0, 0);
    fn_80305C94(tu, wr, wr, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    fn_80022254(tu, 1);
    fn_80305A40(tv, v, w2, h2, 1, 0, 0, 0);
    fn_80305C94(tv, wr, wr, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    fn_80022254(tv, 2);
    fn_80306EA0(3, *c);
    fn_80304314(0x80, 7, 4);
    FF = x0; FF = y0; FF = z0; FF = 0; FF = 0;
    FF = x0 + tw; FF = y0; FF = z0; FF = 1; FF = 0;
    FF = x0 + tw; FF = y0 + th; FF = z0; FF = 1; FF = 1;
    FF = x0; FF = y0 + th; FF = z0; FF = 0; FF = 1;
}
}
