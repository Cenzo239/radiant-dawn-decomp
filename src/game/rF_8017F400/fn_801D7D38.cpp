/* fn_801D7D38: exact (round m13: block locals of both branches moved to the top as separate variables
   by/bx and by2/bx2, declaration order by search). Address is in rF's range; helpers from rR_80175E5C/fn_801D772C.cpp, body from rR_80175E5C/wip/fn_801D772C.cpp */
/* Window parts built from the sheet sprite primitives. The primitives are declared here
   with s16 and u16 arguments, which is what the callers extend to; the definitions in
   fn_801D60D0.cpp take int. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"

extern "C" {
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_8041EF80[0x20];
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, u16 fl, const Color& c, int flip);
void fn_801D64AC(s16 x, s16 y, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D65EC(s16 x, s16 y, u16 fl, Rect* src, const Color* c, int flip);
void fn_801D68E4(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6A4C(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6BC0(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6D68(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6F1C(s16 x, s16 y, s16 w, s16 h, u16 fl, const Color& c);


extern void* lbl_804CBDF8;

#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
#define SPRB(i) fn_80006A64(lbl_804CBE08, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }

#define ONE(name, idx, rect) \
void name(s16 x, s16 y, u16 fl) { \
    SPR(idx); \
    fn_801D60D0(x, y, RW(rect), RH(rect), fl, &rect, 0); \
}

#pragma use_lmw_stmw on


#pragma use_lmw_stmw off










#pragma use_lmw_stmw on
#define WAVE(name, a, b, ra, rb) \
void name(s16 x, s16 y, u16 fl) { \
    s16 rem = 0x260 - x; \
    SPR(a); \
    fn_801D60D0(x, y, RW(ra), RH(ra), fl, &ra, 0); \
    fn_801D60D0(x, y + RH(ra), RW(ra), RH(ra), fl, &ra, 2); \
    s16 w = RW(ra); \
    if (rem > w) { \
        SPR(b); \
        int nr = rem - w; \
        int nx = x + w; \
        fn_801D620C(nx, y, nr, RH(rb), fl, &rb, 0); \
        fn_801D620C(nx, y + RH(rb), nr, RH(rb), fl, &rb, 2); \
    } \
}



void fn_8006E610(int, int, int, int, int, int);
int fn_801D09F0();




#pragma use_lmw_stmw on

#pragma use_lmw_stmw off






extern void* lbl_804CBE08;



#pragma use_lmw_stmw on



#pragma use_lmw_stmw off

extern u8 lbl_804CF840[8];
}
static inline void Inner(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    int y2, x2;
    SPR(0x78);
    fn_801D60D0(x, y, RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 0);
    x2 = x + w;
    fn_801D60D0(x2 - RW(lbl_804CBD50), y, RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 1);
    y2 = y + h;
    fn_801D60D0(x, y2 - RH(lbl_804CBD50), RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 2);
    fn_801D60D0(x2 - RW(lbl_804CBD50), y2 - RH(lbl_804CBD50), RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 3);
    SPR(0x79);
    fn_801D620C(x + RW(lbl_804CBD50), y, w - RW(lbl_804CBD50) * 2, RH(lbl_804CBD50), fl, &lbl_804CBD58, 0);
    fn_801D620C(x + RW(lbl_804CBD50), y2 - RH(lbl_804CBD50), w - RW(lbl_804CBD50) * 2, RH(lbl_804CBD50), fl, &lbl_804CBD58, 2);
    SPR(0x7A);
    fn_801D620C(x, y + RH(lbl_804CBD50), RW(lbl_804CBD50), h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD60, 0);
    fn_801D620C(x2 - RW(lbl_804CBD50), y + RH(lbl_804CBD50), RW(lbl_804CBD50), h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD60, 1);
    SPR(0x7B);
    fn_801D620C(x + RW(lbl_804CBD50), y + RH(lbl_804CBD50), w - RW(lbl_804CBD50) * 2, h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD68, 0);
}
extern "C" {
#define BIGWIN(name) \
void name(s16 x, s16 y, s16 w, s16 h, u16 fl) { \
    int ch = RH(lbl_804CBD78); \
    int cw = RW(lbl_804CBD80); \
    SPR(0x7F); \
    int iw = w - cw * 2; \
    int ix = x + cw; \
    fn_801D620C(ix, y, iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 0); \
    fn_801D620C(ix, y + h - RH(lbl_804CBD78), iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 2); \
    SPR(0x80); \
    int ih = h - ch * 2; \
    int iy = y + ch; \
    fn_801D620C(x, iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 0); \
    fn_801D620C(x + w - RW(lbl_804CBD80), iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 1); \
    Alpha(3.0f); \
    Color a(lbl_804CF840[4], lbl_804CF840[5], lbl_804CF840[6], lbl_804CF840[7]); \
    Color b(a); \
    fn_801D6388(ix, iy, iw, ih, fl, b, 0); \
    Alpha(-3.0f); \
    Alpha(2.9f); \
    Inner(x + 0xC, y + 0xE0, w - 0x18, h - 0xEC, 0x10); \
    Alpha(-2.9f); \
}

#pragma use_lmw_stmw off






extern u8 lbl_804CF7FF[8];
typedef unsigned long long u64;
u64 OSGetTime();
u64 fn_8028C418(u64, u64);
u64 fn_8028C634(u64, u64);
f64 fn_8028C764(u64);
f64 fn_80295940(f64);
void fn_80006B84(void*, void*, void*, int, int);
#define ALPHAQ(v) do { fn_8007E154(); fn_8007E720(v); fn_8007E164(); } while (0)





void fn_801D7D38(s16 x, s16 y, int unused, s16 w, s16 top, int bh, const Color& col, u16 fl) {
    f32 s;
    int by;
    int bx;
    void* st;
    Rect* r;
    int hh;
    int by2;
    int bx2;
    st = fn_8007E4C4(&s);
    SPRB(2);
    Alpha(-0.2f);
    fn_801D60D0(x, y - RH(lbl_804CBDE8), RW(lbl_804CBDE8), RH(lbl_804CBDE8), fl, &lbl_804CBDE8, 0);
    fn_801D60D0(x, y + w, RW(lbl_804CBDE8), RH(lbl_804CBDE8), fl, &lbl_804CBDE8, 2);
    Alpha(0.2f);
    SPRB(3);
    fn_801D620C(x - 4, y, RW(lbl_804CBDF0), w, fl, &lbl_804CBDF0, 0);
    Alpha(-0.1f);
    r = &lbl_804CBDD8;
    if (bh >= RH(lbl_804CBDD8) * 2) {
        SPRB(0);
        by = y + top;
        bx = x + 2;
        fn_801D68E4(bx, by, RW(*r), RH(*r), fl, r, Color(col), 0);
        fn_801D68E4(bx, bh + by - RH(*r), RW(*r), RH(*r), fl, r, Color(col), 2);
        SPRB(1);
        fn_801D6BC0(bx, by + RH(lbl_804CBDD8), RW(lbl_804CBDE0), bh - RH(lbl_804CBDD8) * 2, fl, &lbl_804CBDE0, Color(col), 0);
    } else {
        SPRB(0);
        hh = bh >> 1;
        by2 = y + top;
        bx2 = x + 2;
        fn_801D6BC0(bx2, by2, RW(*r), hh, fl, r, Color(col), 0);
        fn_801D6BC0(bx2, hh + by2, RW(*r), hh, fl, r, Color(col), 2);
    }
    Alpha(0.1f);
    fn_8007E478(st, s);
}

/* fn_801DB3F4: 3 of 223 words differ */


/* fn_801D820C: 161 of 212 words differ */


/* fn_801D7014: 25 of 296 words differ, only cw/ch swapped between r16 and r17. Declaration order found by hill climbing. */



/* fn_801DAEF4 (and the identical fn_801DC2B0): 270 of 320 words, frame 0x10 too large. The second half is the inlined nine-slice Inner(x + 0xC, y + 0xE0, w - 0x18, h - 0xEC, 0x10), which compiles to the right instructions, but the original reuses r25 for w and needs two fewer saved registers. */



}
