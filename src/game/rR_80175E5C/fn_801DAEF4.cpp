#pragma inline_max_size(4000)
#pragma inline_max_total_size(40000)
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"
extern "C" {
extern u8 lbl_8041EF60[0x20];
extern void* lbl_804CBDF8;
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, int fl, const Color& c, int flip);
#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }
struct PC { u8 r, g, b, a; };
static inline void Fill(s16 x, s16 y, s16 w, s16 h, int fl, const PC& c) {
    fn_801D6388(x, y, w, h, fl, Color(c.r, c.g, c.b, c.a), 0);
}
static inline void Inner(s16 x, s16 y, s16 w, s16 h, int fl) {
    Rect* a;
    SPR(0x78);
    a = &lbl_804CBD50;
    fn_801D60D0(x, y, RW(*a), RH(*a), fl, a, 0);
    fn_801D60D0(x + w - RW(*a), y, RW(*a), RH(*a), fl, a, 1);
    fn_801D60D0(x, y + h - RH(*a), RW(*a), RH(*a), fl, a, 2);
    fn_801D60D0(x + w - RW(*a), y + h - RH(*a), RW(*a), RH(*a), fl, a, 3);
    SPR(0x79);
    fn_801D620C(x + RW(*a), y, w - RW(*a) * 2, RH(*a), fl, &lbl_804CBD58, 0);
    fn_801D620C(x + RW(*a), y + h - RH(*a), w - RW(*a) * 2, RH(*a), fl, &lbl_804CBD58, 2);
    SPR(0x7A);
    fn_801D620C(x, y + RH(*a), RW(*a), h - RH(*a) * 2, fl, &lbl_804CBD60, 0);
    fn_801D620C(x + w - RW(*a), y + RH(*a), RW(*a), h - RH(*a) * 2, fl, &lbl_804CBD60, 1);
    SPR(0x7B);
    fn_801D620C(x + RW(*a), y + RH(*a), w - RW(*a) * 2, h - RH(*a) * 2, fl, &lbl_804CBD68, 0);
}
static inline void Body_fn_801DAEF4(s16 x, s16 y, s16 w, s16 h, int fl, int dy, int dh) {
    /*P*/
    Rect* a = &lbl_804CBD78;
    Rect* b = &lbl_804CBD80;
    int ny;
    int nh;
    int nx;
    int nw;
    s16 bh;
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
    PC q = {0, 0, 0, 0x99};
    Fill(nx, ny, nw, nh, fl, q);
    Alpha(-3.0f);
    Alpha(2.9f);
    Inner(x + 0xC, y + dy, w - 0x18, h - dh, 0x10);
    Alpha(-2.9f);
}
void fn_801DAEF4(s16 x, s16 y, s16 w, s16 h, int fl) { Body_fn_801DAEF4(x, y, w, h, fl, 0xE0, 0xEC); }
void fn_801DC2B0(s16 x, s16 y, s16 w, s16 h, int fl) { Body_fn_801DAEF4(x, y, w, h, fl, 0x2C, 0x38); }
}
