/* 17 words: x,y string registers and the hoisted 0x4330 take the wrong saved registers; hill.py stuck. */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_801BCA5C(f32 v);
const char* fn_800CEB4C(void);
const char* fn_800CEC24(void);
const char* fn_800CEDD4(void);
const char* fn_800CEEAC(void);
const char* fn_800CF2D8(void);
void fn_80291110(char* a, const char* b);
void fn_801C6D9C(const char* s, int a, int b, int c);

void fn_802662EC(void) {
    /*P*/
    int a;
    int b;
    u8 col;
    u8 al;
    char buf[0x60];
    char sub[0x20];
    /*E*/
    a = (int)fn_8017F68C(0.0f, 255.0f, lbl_804CC008->m52, 24.0f, 0);
    b = (int)fn_8017F68C(0.0f, 255.0f, lbl_804CC008->m50, 24.0f, 0);
    if (lbl_804CC008->m4C == 1) {
        lbl_804CC008->m50 += 2;
        if (lbl_804CC008->m50 > 0x18) {
            lbl_804CC008->m50 = 0x18;
        }
        lbl_804CC008->m52 += 1;
        if (lbl_804CC008->m52 > 0x18) {
            lbl_804CC008->m52 = 0x18;
        }
    } else {
        lbl_804CC008->m50 -= 2;
        if (lbl_804CC008->m50 < 0) {
            lbl_804CC008->m50 = 0;
        }
    }
    al = (u8)a < 0x5A ? 0 : (u8)a;
    col = al * (u8)b / 255;
    fn_801BCA5C(-7.0f);
    {
    /*P*/
    const char* g;
    const char* f;
    const char* e;
    const char* d;
    const char* c;
    const char* y;
    const char* x;
    const char* s;
    /*E*/
    s = lbl_80372C90;
    x = fn_800D0864(s + 0x199);
    y = fn_800CEC24();
    c = fn_800D0864(s + 0x24C);
    d = fn_800CEDD4();
    e = fn_800D0864(s + 0x242);
    f = fn_800CEEAC();
    g = fn_800D0864(s + 0x191);
    fn_80290DDC(buf, s + 0x22E, fn_800CF2D8(), g, f, e, d, c, y, x);
    if (lbl_804CC008->m4E == 1) {
        g = fn_800D0864(s + 0x257);
        fn_80290DDC(sub, s + 0x1C2, fn_800CEB4C(), g);
        fn_80291110(buf, sub);
    }
    }
    fn_801C6D9C(buf, col, (u8)b, 0);
    fn_801BCA5C(7.0f);
}

}
