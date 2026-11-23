/* functionally equal (check_regs: regs, 4 words). Address is in rF's range; source from rR_80175E5C/wip/fn_801DA800.cpp
   with `yy = y + 3` moved after xx (round 18; fixes the schedule after fn_8007E4C4). */
/* fn_801DA800: 9 of 399 words differ: the sel * 0x1C temporary wants r18 and one yb sum wants other volatile registers. Behind a one-line wrapper the temporary gets r18, but the loop counter and stack slots then change. Compiles on its own. */
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
static inline int Add(int a, int b) { return a + b; }
static inline s16 RectH(const Rect& r) { return r.y1 - r.y0; }
struct PC { u8 r, g, b, a; };
static inline void Fill(s16 x, s16 y, s16 w, s16 h, u16 fl, const PC& c) {
    fn_801D6388(x, y, w, h, fl, Color(c.r, c.g, c.b, c.a), 0);
}

static inline void Tex(void* tex, u16 f) {
    fn_8007E154();
    fn_8007E174(tex, f);
    fn_8007E164();
}

void fn_801DA800(s16 x, s16 y, s16 h, int sel, int n, int fl) {
    /*P*/
    Rect* d;
    Rect* b;
    Rect* a = &lbl_804CBCC0;
    void* st;
    s16 xx;
    s16 yy;
/*E*/
    f32 sv;
    Rect s;
    s.x0 = 0;
    s.y0 = 3;
    s.x1 = 0x1D;
    s.y1 = 0x1F;
    Alpha(0.1f);
    SPR(0x5D);
    fn_801D60D0(x, y - RH(*a) + 4, RW(*a), RH(*a), fl, a, 0);
    SPR(0x5E);
    fn_801D60D0(x, y + h - 4, RW(lbl_804CBCC8), RH(lbl_804CBCC8), fl, &lbl_804CBCC8, 0);
    Alpha(-0.1f);
    b = &lbl_804CBC40;
    SPR(0x42);
    fn_801D620C(x + RW(*a) - RW(lbl_804CBC40), y, RW(lbl_804CBC40), h, fl, &lbl_804CBC40, 0);
    if (sel < n) {
        fn_801D620C(x, y, RW(*b), s.y0 + sel * 0x1C, fl, b, 0);
        s16 sh;
        int yb;
        int top;
        int h2;
        top = s.y0 + sel * 0x1C;
        sh = RectH(s);
        yb = y + sh;
        yb = yb + top;
        h2 = sh + top;
        fn_801D620C(x, yb, RW(*b), h - h2, fl, b, 0);
    } else {
        fn_801D620C(x, y, RW(*b), h, fl, b, 0);
    }
    st = fn_8007E4C4(&sv);
    /*Q*/d = &lbl_804CBC90;
    xx = x - RW(lbl_804CBC90) + 4;
    yy = y + 3;
    for (int i = 0; i < n; i++) {
        if (sel == i) {
            Alpha(-0.5f);
            SPR(0x4C);
            fn_801D60D0(xx, yy, RW(*d), RH(*d), fl, d, 0);
            Alpha(0.5f);
            Alpha(0.1f);
            SPR(0x62);
            fn_801D620C(xx + 2, yy + 2, RW(*d) - 2, RH(s), fl, &s, 0);
            Alpha(-0.1f);
        } else {
            Alpha(0.1f * i + 0.1f);
            SPR(0x4C);
            fn_801D60D0(xx, yy, RW(*d), RH(*d), fl, d, 0);
            Alpha(0.1f);
            SPR(0x62);
            PC q = {0x80, 0x80, 0x80, 0xFF};
            fn_801D68E4(xx + 2, yy + 2, RW(*d) - 2, RH(s), fl, &s, Color(q.r, q.g, q.b, q.a), 0);
            Alpha(-0.1f);
            Alpha(-(0.1f * i + 0.1f));
        }
        yy = yy + 0x1C;
    }
    fn_8007E478(st, sv);
    Alpha(3.0f);
    SPR(0x62);
    s16 w = RW(lbl_804CBCC0);
    if (w != 0 && h != 0) {
        Tex(lbl_8041EF60, fl | 1);
        fn_800800D4(10);
        fn_80080388(x, y, w, h);
        fn_800803C8(lbl_804CBCD0.x0, lbl_804CBCD0.y0, RW(lbl_804CBCD0), RH(lbl_804CBCD0));
        fn_800808F8(0.0f, 0.0f);
        fn_80080308();
    }
    Alpha(-3.0f);
}
}
