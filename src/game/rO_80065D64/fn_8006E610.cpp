/* Window frames with shadow, bars, and pulsing sprites: fn_8006E610, fn_8006FB94, fn_800712E8, fn_80072ACC. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off
struct Tex {
    u32 d[8];
    u16 w;
    u16 h;
};
extern "C" {
extern void* lbl_804CB58C;
extern void fn_80006A64(void*, Tex*, u16);
extern u16 fn_80305DF8(Tex*);
extern u16 fn_80305E0C(Tex*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(Tex*, int);
extern void fn_8007E720(f32);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080410(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80080C24(p32arg);
#else
extern void fn_80080C24(int);
#endif
extern void fn_80080308(void);
extern Tex fn_8006E098(int x, int y, int w, int h, int u0, int v0, int u1, int v1, int color, u8 alpha, u16 id, int flags);

static inline void TexLoad(Tex* t, u16 id) {
    fn_80006A64(lbl_804CB58C, t, id);
    t->w = fn_80305DF8(t);
    t->h = fn_80305E0C(t);
}

static inline Tex Spr(int x, int y, int w, int h, int color, u8 alpha, u16 id, int flags) {
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

static inline Tex Spr3(int x, int y, int color, u8 alpha, u16 id, int flags) {
    Tex t0;
    TexLoad(&t0, id);
    int w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

void fn_8006E610(int x, int y, int w, int h, int color, int f) {
    /*P*/
    int cx4;
    int cx2;
    int cx3;
    int yb2;
    int yy2;
    int mw;
    int yb;
    int mh2;
    int cx;
    int hw;
    int cx5;
    int yy;
    int mh;
    int c;
/*E*/
    hw = (w - 0x40) / 2;
    c = color + 0x41;
    if (hw < 0) {
        hw = 0;
    }
    Spr3(x, y + 6, c, 0xD2, 0x11, 0);
    cx = x + 0x20;
    fn_8006E098(cx, y + 6, hw, 10, 0, 0, 0x60, 9, c, 0xD2, 0x12, 0);
    cx += hw;
    fn_8006E098(cx, y + 6, hw, 10, 0, 0, 0x60, 9, c, 0xD2, 0x12, 1);
    cx += hw;
    Spr3(cx, y, c, 0xD2, 0x13, 3);
    mh = h - 0x20;
    yy = y + 0x10;
    if (mh < 0) {
        mh = 0;
    }
    fn_8006E098(x, yy, 0x20, mh, 0, 0, 0x20, 9, c, 0xD2, 0x13, 0);
    cx2 = x + 0x20;
    fn_8006E098(cx2, yy, hw, mh, 0, 0, 0x60, 9, c, 0xD2, 0x12, 0);
    cx2 += hw;
    fn_8006E098(cx2, yy, hw, mh, 0, 0, 0x60, 9, c, 0xD2, 0x12, 1);
    cx2 += hw;
    fn_8006E098(cx2, yy, 0x20, mh, 0, 0, 0x20, 9, c, 0xD2, 0x13, 1);
    yb = y + mh + 0x10;
    Spr3(x, yb, c, 0xD2, 0x13, 0);
    cx3 = x + 0x20;
    fn_8006E098(cx3, yb, hw, 10, 0, 0, 0x60, 9, c, 0xD2, 0x12, 0);
    cx3 += hw;
    fn_8006E098(cx3, yb, hw, 10, 0, 0, 0x60, 9, c, 0xD2, 0x12, 1);
    cx3 += hw;
    Spr3(cx3, yb - 6, c, 0xD2, 0x11, 3);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    mw = w - 0x40;
    if (mw < 0) {
        mw = 0;
    }
    Spr3(x, y, 1, 0xFF, 0xD, 0);
    cx4 = x;
    cx4 += 0x20;
    Spr(cx4, y, mw, 8, 1, 0xFF, 0xF, 0);
    cx4 += mw;
    Spr3(cx4, y, 1, 0xFF, 0xE, 0);
    mh2 = h - 0x20;
    yy2 = y + 0x10;
    if (mh2 < 0) {
        mh2 = 0;
    }
    Spr(x, yy2, 8, h - 0x18, 1, 0xFF, 0x10, 0);
    Spr(x + w - 8, yy2, 8, h - 0x18, 1, 0xFF, 0x10, 1);
    yb2 = y + mh2 + 0x10;
    Spr3(x, yb2, 1, 0xFF, 0xE, 3);
    cx5 = x;
    cx5 += 0x20;
    Spr(cx5, yb2 + 8, mw, 8, 1, 0xFF, 0xF, 2);
    cx5 += mw;
    Spr3(cx5, yb2, 1, 0xFF, 0xD, 3);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

void fn_8006FB94(int color, f32 x, f32 y, f32 w, f32 h) {
    /*P*/
    int ix2;
    int iy2;
    int ix;
    int iy;
    int hw;
    int iy3;
    int ix3;
    int mh;
/*E*/
    ix = x;
    iy = y;
    hw = w / 2.0f;
    if (hw < 0) {
        hw = 0;
    }
    fn_8006E098(ix, iy + 3, hw, 5, 0, 0, 0x60, 9, color, 0xD2, 0x12, 0);
    ix += hw;
    fn_8006E098(ix, iy + 3, hw, 5, 0, 0, 0x60, 9, color, 0xD2, 0x12, 1);
    ix2 = x;
    iy2 = 8.0f + y;
    mh = h - 16.0f;
    if (mh < 0) {
        mh = 0;
    }
    fn_8006E098(ix2, iy2, hw, mh, 0, 0, 0x60, 9, color, 0xD2, 0x12, 0);
    ix2 += hw;
    fn_8006E098(ix2, iy2, hw, mh, 0, 0, 0x60, 9, color, 0xD2, 0x12, 1);
    ix3 = x;
    iy3 = (8.0f + y) + mh;
    fn_8006E098(ix3, iy3, hw, 5, 0, 0, 0x60, 9, color, 0xD2, 0x12, 0);
    ix3 += hw;
    fn_8006E098(ix3, iy3, hw, 5, 0, 0, 0x60, 9, color, 0xD2, 0x12, 1);
}

extern int fn_801D09F0(void);
extern void* lbl_804CB580;
extern void fn_80080348(f32, f32, f32, f32);
struct Color { u8 r, g, b, a; };
extern Color* fn_800CD204(u8);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080508(Color*);
extern void fn_800804F4(u8);
extern s64 OSGetTime(void);
extern s64 fn_8028C418(s64, s64);
extern s64 fn_8028C634(s64, s64);
extern f32 fn_8028C764(s64);
extern double fn_80295940(double);
void fn_80072ACC(int x, int y, int w, int color, int p5, int p6, int f) {
    /*P*/
    void* set;
    int xm;
    int y1;
    int hw;
    int x0;
    int x1;
    int tw;
    int th;
    int a;
/*E*/
    set = lbl_804CB58C;
    f32 pi = 3.141592f;
    if (w <= 0x50) {
        w = 0x50;
    }
    f32 ms = fn_8028C764(fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 >> 2) / 1000), 1500)) / 1500.0f;
    if (f == 0) {
        a = 0x28;
    } else {
        u32 hi = 0x4B;
        a = 0x28;
        f32 r = (f32)hi - (f32)(u32)a;
        f32 c = fn_80295940((2.0f * pi) * ms);
        a = 0.5f * (r * (1.0f + c)) + (f32)(u32)a;
    }
    Tex t;
    fn_80006A64(set, &t, 0x23);
    t.w = fn_80305DF8(&t);
    t.h = fn_80305E0C(&t);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    tw = t.w;
    th = t.h;
    fn_800800D4(1);
    hw = w / 2;
    x0 = x - hw;
    fn_80080348(x0, y - 10, 0.0f, 0.0f);
    x1 = tw + x0;
    y1 = th + y - 10;
    fn_80080368(x1, y1, tw, th);
    {
        Color c = *fn_800CD204(color);
        fn_80080508(&c);
    }
    fn_800804F4(a);
    fn_80080308();
    fn_800800D4(1);
    x += hw;
    xm = x - tw;
    fn_80080348(xm, y - 10, tw, 0.0f);
    fn_80080368(x, y1, 0.0f, th);
    {
        Color c = *fn_800CD204(color);
        fn_80080508(&c);
    }
    fn_800804F4(a);
    fn_80080308();
    fn_80006A64(set, &t, 0x24);
    t.w = fn_80305DF8(&t);
    t.h = fn_80305E0C(&t);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(x1, y - 10, 0.0f, 0.0f);
    fn_80080368(xm, y1, t.w, t.h);
    {
        Color c = *fn_800CD204(color);
        fn_80080508(&c);
    }
    fn_800804F4(a);
    fn_80080308();
}
extern int fn_8017F990(int, int);
extern double fn_80295534(double);
void fn_800712E8(int x, int y, int f) {
    /*P*/
    f32 d;
    f32 sw;
    f32 sh;
    f32 sh2;
    f32 ox;
    f32 ox2;
    f32 sw2;
/*E*/
    if (f == 0) {
        Tex t;
        fn_80006A64(lbl_804CB580, &t, 0x13);
        t.w = fn_80305DF8(&t);
        t.h = fn_80305E0C(&t);
        fn_8007E154();
        fn_8007E174(&t, 0x10);
        fn_8007E164();
        sw = t.w;
        sh = t.h;
        ox = 0.0f;
        if (fn_801D09F0()) {
            sw *= 0.7638191f;
            ox = (f32)t.w - sw;
        }
        fn_800800D4(1);
        fn_80080388((f32)(x - 0x20) + ox, y + 0xC, sw, sh);
        fn_80080308();
    } else {
        int r = fn_8017F990(0, 500);
        f32 s = fn_80295534(6.2831855f * ((f32)r / 500.0f));
        d = 4.0f * (1.0f + s);
        Tex t;
        fn_80006A64(lbl_804CB580, &t, 0x13);
        t.w = fn_80305DF8(&t);
        t.h = fn_80305E0C(&t);
        fn_8007E154();
        fn_8007E174(&t, 0x10);
        fn_8007E164();
        sw2 = t.w;
        sh2 = t.h;
        ox2 = 0.0f;
        if (fn_801D09F0()) {
            sw2 *= 0.7638191f;
            ox2 = (f32)t.w - sw2;
        }
        fn_800800D4(1);
int ix = (f32)(x - 0x20) - d;
        f32 q0 = x;
        int iy = (f32)y + d / 2.0f;
        f32 fx = ix;
        f32 q2 = x;
        f32 fy = iy + 0xC;
        fn_80080388(fx + ox2, fy, sw2, sh2);
        fn_80080308();
    }
}
}
