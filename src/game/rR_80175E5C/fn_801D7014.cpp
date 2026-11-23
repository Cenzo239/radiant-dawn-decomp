/* Window parts built on the sheet primitives, with int flags: fl | 2 then keeps its clrlwi. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"
extern "C" {
extern u8 lbl_8041EF60[0x20];
extern void* lbl_804CBDF8;
extern u8 lbl_804CBA88[8];
void fn_801D087C();
void fn_801D08E4();
void fn_8007E84C(int);
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, int fl, const Color& c, int flip);
#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }
void fn_801D7014(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    /*P*/
    Rect* ra = &lbl_804CBA90;
    Rect* rb = &lbl_804CBAA0;
    s16 cw;
    int y1;
    s16 th;
    int y2;
    int hw;
    int x2;
    s16 ch;
    int rw;
    f32 s;
    int mx;
    s16 iw;
    int x1;
    s16 ih;
    void* st;
    int y3;
/*E*/
    cw = RW(*ra);
    iw = w - cw * 2;
    ch = RH(*ra);
    ih = h - ch * 2;
    th = RH(*rb);

    st = fn_8007E4C4(&s);
    SPR(1);
    fn_801D60D0(x, y, RW(*ra), RH(*ra), fl, ra, 0);
    x2 = x + (w - cw);
    fn_801D60D0(x2, y, RW(*ra), RH(*ra), fl, ra, 1);
    y2 = y + (h - ch);
    fn_801D60D0(x, y2, RW(*ra), RH(*ra), fl, ra, 2);
    fn_801D60D0(x2, y2, RW(*ra), RH(*ra), fl, ra, 3);
    SPR(2);
    y1 = y + ch;
    fn_801D60D0(x, y1, RW(lbl_804CBA98), ih, fl, &lbl_804CBA98, 0);
    fn_801D60D0(x + (w - RW(lbl_804CBA98)), y1, RW(lbl_804CBA98), ih, fl, &lbl_804CBA98, 0);
    SPR(3);
    x1 = x + cw;
    fn_801D60D0(x1, y, iw, RH(*rb), fl, rb, 0);
    fn_801D60D0(x1, y + (h - RH(*rb)), iw, RH(*rb), fl, rb, 2);
    Alpha(2.0f);
    SPR(4);
    y3 = y + th;
    fn_801D60D0(x, y3, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 0);
    fn_801D60D0(x2, y3, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 1);
    fn_801D60D0(x, y2, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 2);
    fn_801D60D0(x2, y2, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 3);
    fn_801D620C(x, y1, w, ih, fl, &lbl_804CBAA8, 0);
    SPR(5);
    hw = iw >> 1;
    fn_801D620C(x1, y3, hw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 0);
    rw = iw - hw;
    mx = hw + x1;
    fn_801D620C(mx, y3, rw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 1);
    fn_801D620C(x1, y2, hw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 0);
    fn_801D620C(mx, y2, rw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 1);
    Alpha(-2.0f);
    fn_8007E478(st, s);
}

#pragma use_lmw_stmw on
static inline void In(s16 x, s16 y, int fl) {
    int i;
    for (i = 0x51; i <= 0x5C; i++) {
        SPR(i);
        fn_801D60D0(x, y, RW(lbl_804CBCB8), RH(lbl_804CBCB8), fl, &lbl_804CBCB8, 0);
        x += RW(lbl_804CBCB8) + 4;
    }
}
void fn_801DA184(s16 x, s16 y, int unused, int fl) {
    In(x, y, fl);
}
#pragma use_lmw_stmw off

struct PC { u8 r, g, b, a; };
static inline void Line(s16 x0, s16 y0, s16 x1, s16 y1, const PC& c, int fl) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    fn_800800D4(4);
    fn_800803F0(0.5f + x0, 0.5f + y0, 0.5f + x1, 0.5f + y1);
    fn_80080508(*(Color*)&c);
    fn_80080308();
}

void fn_801D77BC(s16 x, s16 y, int fl) {
    Rect* r = &lbl_804CBAC0;
    s16 w = RW(*r);
    fn_801D087C();
    fn_8007E84C(3);
    SPR(0);
    fn_801D60D0(x + w + 4, y, RW(*(Rect*)lbl_804CBA88), RH(*(Rect*)lbl_804CBA88), fl, (Rect*)lbl_804CBA88, 0);
    SPR(6);
    fn_801D60D0(x, y + 0xC, RW(*r), RH(*r), fl, r, 0);
    s16 yy = y + 0x13;
    PC c;
    c.r = 0x33;
    c.g = 0x33;
    c.b = 0x33;
    c.a = 0xFF;
    Line(x + 0x16, yy, 0x260, yy, c, fl);
    fn_801D08E4();
}
}
