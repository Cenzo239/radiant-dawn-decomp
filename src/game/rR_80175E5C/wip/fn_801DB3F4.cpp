/* fn_801DB3F4: 2 of 223 words differ: fill should share r28 with mid. Compiles on its own. */
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
void fn_801D68E4(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, const Color& c, int flip);
void fn_801D6BC0(s16 x, s16 y, s16 w, s16 h, int fl, Rect* src, const Color& c, int flip);
#define SPRB(i) fn_80006A64(lbl_804CBE08, lbl_8041EF60, i)
extern void* lbl_804CBE08;
static inline void Body_fn_801DB3F4(s16 x, s16 y, int w, int cur, int tot, int page, int fl) {
    /*P*/
    int by;
    int mid;
    s16 fill;
/*E*/
    s16 tw = RW(lbl_804CBC70) + 0x3E;
    s16 bar = (tot * (w - tw)) / page;
    SPR(0x46);
    fn_801D60D0(x - RW(lbl_804CBC60), y, RW(lbl_804CBC60), RH(lbl_804CBC60), fl, &lbl_804CBC60, 0);
    SPR(0x47);
    fn_801D620C(x, y, tw - RW(lbl_804CBC70), RH(lbl_804CBC68), fl, &lbl_804CBC68, 0);
    SPR(0x48);
    int bx = x + tw;
    fn_801D60D0(bx - RW(lbl_804CBC70), y, RW(lbl_804CBC70), RH(lbl_804CBC70), fl, &lbl_804CBC70, 0);
    SPR(0x49);
    fn_801D620C(bx, y, bar, RH(lbl_804CBC78), fl, &lbl_804CBC78, 0);
    SPR(0x4A);
    fn_801D60D0(bar + bx, y, RW(lbl_804CBC80), RH(lbl_804CBC80), fl, &lbl_804CBC80, 0);
    fill = (bar * cur) / tot;
    if (fill != 0) {
        Alpha(-0.1f);
        mid = (s16)(fill - (RW(lbl_804CBC48) + RW(lbl_804CBC58)));
        if (mid < 0) mid = 0;
        SPR(0x43);
        by = y + 1;
        fn_801D60D0(bx, by, RW(lbl_804CBC48), RH(lbl_804CBC48), fl, &lbl_804CBC48, 0);
        if (mid > 0) {
            SPR(0x44);
            fn_801D620C(bx + RW(lbl_804CBC48), by, mid, RH(lbl_804CBC50), fl, &lbl_804CBC50, 0);
        }
        SPR(0x45);
        fn_801D60D0(RW(lbl_804CBC48) + (mid + bx), by, RW(lbl_804CBC58), RH(lbl_804CBC58), fl, &lbl_804CBC58, 0);
        Alpha(0.1f);
    }
}
void fn_801DB3F4(s16 x, s16 y, int w, int cur, int tot, int page, int fl) { Body_fn_801DB3F4(x, y, w, cur, tot, page, fl); }
}
