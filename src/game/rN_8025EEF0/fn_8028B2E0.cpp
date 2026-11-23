/* Health and safety screen: fade and draw */
#include "game/rN_8025EEF0/calls.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern u32 lbl_804CC100;
extern int lbl_804CAB78;
extern u8 lbl_804CC104;
extern void* lbl_804CC0FC;
u32 fn_8028C1A0(f32 v);
void fn_80308090(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_80312F48(void* m, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void fn_80307D98(void* m, int a);
void fn_80312318(void* m);
void fn_8031292C(void* m, f32 a, f32 b, f32 c);
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
void fn_80306DDC(int a, C4* c);
void fn_80021C74(int a);
void fn_80306B24(int a);
void fn_80021BA4(int a, int b, int c, int d);
void fn_80021860(int a, int b, int c);
void fn_80021B68(int a);
void fn_8032DC0C(void* a, void* b, int c);
void fn_80304314(int a, int b, int c);

static const C4 kc = {0xFF, 0xFF, 0xFF, 0};

#define FIFO (*(volatile s16*)0xCC008000)

void fn_8028B2E0(void* p) {
    u8 m2[0x40];
    u8 m1[0x30];
    u8 tex[0x20];
    {
        f32 v = (f32)lbl_804CC100;
        v += 16.666666f;
        lbl_804CC100 = fn_8028C1A0(v);
    }
    switch (lbl_804CAB78) {
    case 0:
        lbl_804CC104 = (int)(255.9f * ((f32)lbl_804CC100 / 250.0f));
        if ((f32)lbl_804CC100 >= 250.0f) {
            lbl_804CC100 = 0;
            lbl_804CAB78 = 1;
            lbl_804CC104 = 0xFF;
        }
        break;
    case 1:
        if ((f32)lbl_804CC100 >= 1000.0f) {
            lbl_804CC100 = 0;
            lbl_804CAB78 = 2;
        }
        break;
    case 2:
        lbl_804CC104 = (int)(255.9f * ((250.0f - (f32)lbl_804CC100) / 250.0f));
        if ((f32)lbl_804CC100 >= 250.0f) {
            lbl_804CC100 = 0;
            lbl_804CAB78 = -1;
            lbl_804CC104 = 0;
            fn_80083B78(p);
        }
        break;
    }
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    fn_80312F48(m2, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
    fn_80307D98(m2, 1);
    if (fn_801D09F0() != 0) {
        fn_8031292C(m1, 0.7638191f, 1.0f, 1.0f);
    } else {
        fn_80312318(m1);
    }
    fn_80307E48(m1, 0x1B);
    fn_803031CC();
    fn_80303200(7, 9, 0, 3, 0);
    fn_80303200(7, 0xD, 1, 3, 0);
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021BF4(1);
    {
        C4 d;
        C4 c = kc;
        c.a = lbl_804CC104;
        *(u32*)&d = *(u32*)&c;
        fn_80306DDC(1, &d);
    }
    fn_80021CB4(0, 0, 0, 0xFF);
    fn_80021E20(0, 0xF, 0xF, 0xF, 8);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 1, 4, 7);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
    fn_80021C74(0);
    fn_80306B24(0);
    fn_80021BA4(1, 4, 5, 0);
    fn_80021860(0, 3, 0);
    fn_80021784(0x1B);
    fn_80021B68(0);
    fn_8032DC0C(lbl_804CC0FC, tex, 0);
    fn_80022254(tex, 0);
    fn_80304314(0x80, 7, 4);
    FIFO = 0x18; FIFO = 0x48; FIFO = 0; FIFO = 1;
    FIFO = 0x18; FIFO = 0x10; FIFO = 0; FIFO = 0;
    FIFO = 0x50; FIFO = 0x10; FIFO = 1; FIFO = 0;
    FIFO = 0x50; FIFO = 0x48; FIFO = 1; FIFO = 1;
}

}
