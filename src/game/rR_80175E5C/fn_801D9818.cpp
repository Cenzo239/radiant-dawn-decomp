/* Tabbed window parts. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"

extern "C" {
extern u8 lbl_8041EF60[0x20];
extern void* lbl_804CBDF8;
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, int flip);
void fn_801D68E4(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, const Color& c, int flip);
void fn_800808F8(f32, f32);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, int fl, const Color& c, int flip);

#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }
static inline s16 RectH(const Rect& r) { return r.y1 - r.y0; }
struct PC { u8 r, g, b, a; };
static inline void Fill(s16 x, s16 y, s16 w, s16 h, u16 fl, const PC& c) {
    fn_801D6388(x, y, w, h, fl, Color(c.r, c.g, c.b, c.a), 0);
}

void fn_801D9818(s16 x, s16 y, s16 w, int sel, int n, u16 fl) {
    /*P*/
    Rect* a = &lbl_804CBC20;
    Rect* b;
    Rect* c;
    Rect* d;
    Rect* e;
    void* st;
    s16 xx;
    s16 yy;
/*E*/
    f32 sv;
    s16 k = sel * 0x1C;
    Rect s;
    s.x0 = 0;
    s.x1 = 8;
    s.y0 = k + 0xF;
    s.y1 = k + 0x2A;
    Alpha(0.1f);
    SPR(0x3E);
    fn_801D60D0(x - RW(*a) + 4, y, RW(*a), RH(*a), fl, a, 0);
    SPR(0x3F);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBC28), RH(lbl_804CBC28), fl, &lbl_804CBC28, 0);
    Alpha(-0.1f);
    SPR(0x41);
    b = &lbl_804CBC38;
    fn_801D620C(x, y, w, RH(*b), fl, b, 0);
    fn_801D620C(x, y + RH(*a) - RH(*b), w, RH(*b), fl, b, 0);
    Rect t = lbl_804CBC40;
    t.x0 += 1;
    SPR(0x42);
    c = &lbl_804CBC90;
    fn_801D620C(x + RW(*c) + 1, y, RW(t), s.y0, fl, &t, 0);
    fn_801D620C(x + RW(*c) + 1, RectH(s) + (y + s.y0), RW(t), RH(*a) - (s.y0 + RectH(s)), fl, &t, 0);
    st = fn_8007E4C4(&sv);
    xx = x + 4;
    yy = y + 0xE;
    d = &lbl_804CBC90;
    for (int i = 0; i < n; i++) {
        if (sel == i) {
            Alpha(-0.5f);
            SPR(0x4C);
            fn_801D60D0(xx, yy, RW(*d), RH(*d), fl, d, 0);
            Alpha(0.5f);
            SPR(0x40);
            fn_801D620C(xx + 2, yy + 2, RW(*d) - 2, RH(s), fl, &s, 0);
        } else {
            Alpha(0.1f * i + 0.1f);
            SPR(0x4C);
            fn_801D60D0(xx, yy, RW(*d), RH(*d), fl, d, 0);
            Alpha(0.1f);
            PC q = {0, 0, 0, 0xCC};
            fn_801D6388(xx + 2, yy + 2, RW(*d) - 2, RH(s), fl, Color(q.r, q.g, q.b, q.a), 0);
            Alpha(-0.1f);
            Alpha(-(0.1f * i + 0.1f));
        }
        yy = yy + 0x1C;
    }
    fn_8007E478(st, sv);
    Alpha(3.0f);
    e = &lbl_804CBC20;
    PC q2 = {0, 0, 0, 0x99};
    Fill(x, y, RW(*d) + 4, RH(*e), fl, q2);
    SPR(0x40);
    s16 cw = RW(*d);
    fn_801D620C(x + cw + 4, y, w - (cw + 4), RH(*e), fl, &lbl_804CBC30, 0);
    Alpha(-3.0f);
}

}
