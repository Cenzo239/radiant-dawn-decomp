/* Window parts, second batch: same primitives as fn_801D772C.cpp. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"

extern "C" {
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_804CBA88[8];
extern void* lbl_804CBDF8;
extern char lbl_804CBE10;
extern char lbl_804CBE11;
extern Color lbl_8041EF90[4];
extern Color lbl_8041EFA0[4];
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, u16 fl, const Color& c, int flip);
void fn_801D64AC(s16 x, s16 y, u16 fl, Rect* src, const Color* c, int flip);
void fn_801D65EC(s16 x, s16 y, u16 fl, Rect* src, const Color* c, int flip);
void fn_801D68E4(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_8006E610(int a, int b, int c, int d, int e, int f);
void fn_801D087C();
void fn_801D08E4();
void fn_8007E84C(int);

#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }

void fn_801D74B4(int a, int b, int c, int d, int e) {
    f32 s;
    void* st = fn_8007E4C4(&s);
    Alpha(1.0f);
    switch (e) {
    case 5: case 6: case 7: case 8: case 9: case 10:
        e = 0;
        break;
    }
    fn_8006E610(a, b, c, d, e, 1);
    Alpha(-1.0f);
    fn_8007E478(st, s);
}

void fn_801D7574(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    int x1 = x + w;
    s16 t = h / 3;
    Rect a = {x, y, x1, y + t};
    Rect b = {x, y + t, x1, y + t * 2};
    Rect c = {x, y + t * 2, x1, y + t * 3};
    if (!lbl_804CBE10) {
        Color* q = lbl_8041EF90;
        q[0].r = 0; q[0].g = 0; q[0].b = 0; q[0].a = 0;
        q[1].r = 0; q[1].g = 0; q[1].b = 0; q[1].a = 0;
        q[2].r = 0; q[2].g = 0; q[2].b = 0; q[2].a = 0xFF;
        q[3].r = 0; q[3].g = 0; q[3].b = 0; q[3].a = 0xFF;
        lbl_804CBE10 = 1;
    }
    if (!lbl_804CBE11) {
        Color* q = lbl_8041EFA0;
        q[0].r = 0; q[0].g = 0; q[0].b = 0; q[0].a = 0xFF;
        q[1].r = 0; q[1].g = 0; q[1].b = 0; q[1].a = 0xFF;
        q[2].r = 0; q[2].g = 0; q[2].b = 0; q[2].a = 0;
        q[3].r = 0; q[3].g = 0; q[3].b = 0; q[3].a = 0;
        lbl_804CBE11 = 1;
    }
    fn_801D65EC(a.x0, a.y0, fl, &a, lbl_8041EF90, 0);
    fn_801D64AC(b.x0, b.y0, fl, &b, lbl_8041EFA0, 0);
    fn_801D65EC(c.x0, c.y0, fl, &c, lbl_8041EFA0, 0);
}

struct PC { u8 r, g, b, a; };
static const PC k99x = {0, 0, 0, 0x99};
static const PC k99 = {0, 0, 0, 0x99};
static inline void Fill(s16 x, s16 y, s16 w, s16 h, u16 fl, PC c) {
    fn_801D6388(x, y, w, h, fl, Color(c.r, c.g, c.b, c.a), 0);
}

void fn_801DC7B0(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    /*P*/
    Rect* a = &lbl_804CBD78;
    Rect* b = &lbl_804CBD80;
    s16 bh;
    int ny;
    int nw;
    int nh;
    int nx;
    s16 bw;
/*E*/
    bh = RH(*a);
    bw = RW(*b);
    SPR(0x7F);
    nw = w - bw * 2;
    nx = x + bw;
    fn_801D620C(nx, y, nw, RH(*a), fl, a, 0);
    fn_801D620C(nx, y + h - RH(*a), nw, RH(*a), fl, a, 2);
    SPR(0x80);
    nh = h - bh * 2;
    ny = y + bh;
    fn_801D620C(x, ny, RW(*b), nh, fl, b, 0);
    fn_801D620C(x + w - RW(*b), ny, RW(*b), nh, fl, b, 1);
    Alpha(3.0f);
    Fill(nx, ny, nw, nh, fl, k99);
    Alpha(-3.0f);
}

void fn_801DC984(s16 x, s16 y, s16 w, u16 fl) {
    /*P*/
    Rect* a = &lbl_804CBDA8;
    Rect* b = &lbl_804CBDB8;
    int nx;
    int nw;
    s16 aw;
    s16 ah;
    /*E*/
    aw = RW(*a);
    ah = RH(*a);
    SPR(0x85);
    fn_801D60D0(x, y, RW(*a), RH(*a), fl, a, 0);
    fn_801D60D0(x + w - aw, y, RW(*a), RH(*a), fl, a, 1);
    SPR(0x87);
    { int d = aw * -2; nw = d + w; }
    nx = x + aw;
    fn_801D620C(nx, y, nw, RH(*b), fl, b, 0);
    fn_801D620C(nx, y + ah - RH(*b), nw, RH(*b), fl, b, 0);
    Alpha(3.0f);
    SPR(0x89);
    fn_801D620C(x, y, w, ah, fl, &lbl_804CBDC8, 0);
    Alpha(-3.0f);
}

void fn_801DCB44(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    /*P*/
    Rect* a = &lbl_804CBDB0;
    Rect* b = &lbl_804CBDB8;
    Rect* c = &lbl_804CBDC0;
    s16 aw;
    s16 ah;
    int by;
    int ry;
    int bx;
    int nh;
    int nx;
    int nw;
    int ny;
    int rx;
/*E*/
    aw = RW(*a);
    ah = RH(*a);
    SPR(0x86);
    fn_801D60D0(x, y, RW(*a), RH(*a), fl, a, 0);
    by = y + h;
    ry = by - ah;
    fn_801D60D0(x, ry, RW(*a), RH(*a), fl, a, 2);
    bx = x + w;
    rx = bx - aw;
    fn_801D60D0(rx, y, RW(*a), RH(*a), fl, a, 1);
    fn_801D60D0(rx, ry, RW(*a), RH(*a), fl, a, 3);
    SPR(0x87);
    { int d = aw * -2; nw = d + w; }
    nx = x + aw;
    fn_801D620C(nx, y, nw, RH(*b), fl, b, 0);
    fn_801D620C(nx, by - RH(*b), nw, RH(*b), fl, b, 0);
    SPR(0x88);
    { int d = ah * -2; nh = d + h; }
    ny = y + ah;
    fn_801D620C(x, ny, RW(*c), nh, fl, c, 0);
    fn_801D620C(bx - RW(*c), ny, RW(*c), nh, fl, c, 0);
    Alpha(3.0f);
    SPR(0x89);
    fn_801D68E4(x, y, w, h, fl, &lbl_804CBDC8, Color(0xFF, 0xFF, 0xFF, 0xB3), 0);
    Alpha(-3.0f);
}
}
