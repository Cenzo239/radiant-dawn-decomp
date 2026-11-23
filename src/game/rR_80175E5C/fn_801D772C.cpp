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
ONE(fn_801D772C, 0x22, lbl_804CBB40)
ONE(fn_801D7A68, 9, lbl_804CBAD8)
ONE(fn_801D7AF8, 0x2E, lbl_804CBBA0)
ONE(fn_801D7B88, 0x2F, lbl_804CBBA8)
ONE(fn_801D7C18, 0x30, lbl_804CBBB0)
ONE(fn_801D7CA8, 0x31, lbl_804CBBB8)
ONE(fn_801D80EC, 0x20, lbl_804CBB28)
ONE(fn_801D817C, 0x21, lbl_804CBB38)
ONE(fn_801D8C24, 0x25, lbl_804CBB58)
ONE(fn_801D9788, 0x4D, lbl_804CBC98)
ONE(fn_801DA230, 0x4F, lbl_804CBCA8)
ONE(fn_801DA2C0, 0x50, lbl_804CBCB0)
ONE(fn_801DAE3C, 0x7E, lbl_804CBD70)
ONE(fn_801DC220, 0x7E, lbl_804CBD70)

#pragma use_lmw_stmw on


#pragma use_lmw_stmw off
void fn_801D855C(s16 x, s16 y, s16 w, u16 fl) {
    SPR(0x1A);
    fn_801D60D0(x, y, RW(lbl_804CBAF8), RH(lbl_804CBAF8), fl, &lbl_804CBAF8, 2);
    fn_801D60D0(x + (w - RW(lbl_804CBAF8)), y, RW(lbl_804CBAF8), RH(lbl_804CBAF8), fl, &lbl_804CBAF8, 0);
    s16 cw = RW(lbl_804CBAF8);
    SPR(0x19);
    int nw = w - cw * 2;
    int nx = x + cw;
    fn_801D620C(nx, y, nw, RH(lbl_804CBAF0), fl, &lbl_804CBAF0, 0);
    Alpha(1.0f);
    fn_801D6388(nx, y + RH(lbl_804CBAF0), nw, RH(lbl_804CBAF8) - RH(lbl_804CBAF0), fl, Color(0x2F, 0x25, 0x24, 0xB3), 0);
    Alpha(-1.0f);
}

void fn_801D870C(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.1f);
    SPR(0x1B);
    fn_801D60D0(x - RW(lbl_804CBB00) + 4, y, RW(lbl_804CBB00), RH(lbl_804CBB00), fl, &lbl_804CBB00, 0);
    SPR(0x1C);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBB08), RH(lbl_804CBB08), fl, &lbl_804CBB08, 0);
    Alpha(-0.1f);
    SPR(0x19);
    fn_801D620C(x, y, w, RH(lbl_804CBAF0), fl, &lbl_804CBAF0, 0);
    fn_801D620C(x, y + RH(lbl_804CBB00) - RH(lbl_804CBAF0), w, RH(lbl_804CBAF0), fl, &lbl_804CBAF0, 0);
    Alpha(3.0f);
    SPR(0x1D);
    fn_801D620C(x, y, w, RH(lbl_804CBB00), fl, &lbl_804CBB10, 0);
    Alpha(-3.0f);
}

void fn_801D88F4(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.1f);
    SPR(0x2A);
    fn_801D60D0(x - RW(lbl_804CBB80) + 4, y, RW(lbl_804CBB80), RH(lbl_804CBB80), fl, &lbl_804CBB80, 0);
    SPR(0x2B);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBB88), RH(lbl_804CBB88), fl, &lbl_804CBB88, 0);
    Alpha(-0.1f);
    SPR(0x19);
    fn_801D620C(x, y, w, RH(lbl_804CBAF0), fl, &lbl_804CBAF0, 0);
    fn_801D620C(x, y + RH(lbl_804CBB80) - RH(lbl_804CBAF0), w, RH(lbl_804CBAF0), fl, &lbl_804CBAF0, 0);
    Alpha(3.0f);
    SPR(0x2C);
    fn_801D620C(x, y, w, RH(lbl_804CBB80), fl, &lbl_804CBB90, 0);
    Alpha(-3.0f);
}

void fn_801D95A0(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.1f);
    SPR(0x3E);
    fn_801D60D0(x - RW(lbl_804CBC20) + 4, y, RW(lbl_804CBC20), RH(lbl_804CBC20), fl, &lbl_804CBC20, 0);
    SPR(0x3F);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBC28), RH(lbl_804CBC28), fl, &lbl_804CBC28, 0);
    Alpha(-0.1f);
    SPR(0x41);
    fn_801D620C(x, y, w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    fn_801D620C(x, y + RH(lbl_804CBC20) - RH(lbl_804CBC38), w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    Alpha(3.0f);
    SPR(0x40);
    fn_801D620C(x, y, w, RH(lbl_804CBC20), fl, &lbl_804CBC30, 0);
    Alpha(-3.0f);
}

void fn_801D8ADC(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.2f);
    SPR(0x1E);
    fn_801D60D0(x, y, RW(lbl_804CBB18), RH(lbl_804CBB18), fl, &lbl_804CBB18, 0);
    fn_801D60D0(x + (w - RW(lbl_804CBB18)), y, RW(lbl_804CBB18), RH(lbl_804CBB18), fl, &lbl_804CBB18, 3);
    SPR(0x1F);
    fn_801D620C(x + RW(lbl_804CBB18), y, w - RW(lbl_804CBB18) * 2, RH(lbl_804CBB20), fl, &lbl_804CBB20, 0);
    Alpha(-0.2f);
}

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
WAVE(fn_801D8DBC, 0x26, 0x27, lbl_804CBB60, lbl_804CBB68)
WAVE(fn_801D8F10, 0x28, 0x29, lbl_804CBB70, lbl_804CBB78)

void fn_801D9064(s16 x, s16 y, u16 fl) {
    Alpha(-1.0f);
    SPR(0x34);
    fn_801D60D0(x, y, RW(lbl_804CBBD0), RH(lbl_804CBBD0), fl, &lbl_804CBBD0, 0);
    fn_801D60D0(x, y + RH(lbl_804CBBD0) + RH(lbl_804CBBD8), RW(lbl_804CBBD0), RH(lbl_804CBBD0), fl, &lbl_804CBBD0, 2);
    SPR(0x35);
    fn_801D60D0(x, y + RH(lbl_804CBBD0), RW(lbl_804CBBD8), RH(lbl_804CBBD8), fl, &lbl_804CBBD8, 0);
    fn_801D60D0(x + RW(lbl_804CBBD0) - RW(lbl_804CBBD8), y + RH(lbl_804CBBD0), RW(lbl_804CBBD8), RH(lbl_804CBBD8), fl, &lbl_804CBBD8, 1);
    Alpha(1.0f);
    Alpha(1.0f);
    SPR(0x33);
    int ny = y + 6;
    int nx = x + 6;
    fn_801D60D0(nx, ny, RW(lbl_804CBBC8), RH(lbl_804CBBC8), fl, &lbl_804CBBC8, 0);
    fn_801D60D0(nx + RW(lbl_804CBBC8), ny, RW(lbl_804CBBC8), RH(lbl_804CBBC8), fl, &lbl_804CBBC8, 1);
    Alpha(-1.0f);
}

void fn_8006E610(int, int, int, int, int, int);
int fn_801D09F0();


void fn_801D92D0(s16 x, s16 y, int kind, u16 fl) {
    Rect* r;
    int i;
    switch (kind) {
    case 1: i = 0x38; r = &lbl_804CBBF0; break;
    case 2: i = 0x39; r = &lbl_804CBBF8; break;
    case 3: i = 0x3A; r = &lbl_804CBC00; break;
    }
    SPR(i);
    if (fn_801D09F0() != 0) {
        s16 w = 0.7638191f * RW(*r);
        fn_801D620C(x - w, y, w, RH(*r), fl, r, 0);
    } else {
        fn_801D60D0(x - RW(*r), y, RW(*r), RH(*r), fl, r, 0);
    }
}

#pragma use_lmw_stmw on

#pragma use_lmw_stmw off

void fn_801DA350(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.1f);
    SPR(0x3E);
    fn_801D60D0(x - RW(lbl_804CBC20) + 4, y, RW(lbl_804CBC20), RH(lbl_804CBC20), fl, &lbl_804CBC20, 0);
    SPR(0x3F);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBC28), RH(lbl_804CBC28), fl, &lbl_804CBC28, 0);
    Alpha(-0.1f);
    SPR(0x41);
    fn_801D620C(x, y, w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    fn_801D620C(x, y + RH(lbl_804CBC20) - RH(lbl_804CBC38), w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    Alpha(3.0f);
    SPR(0x40);
    fn_801D620C(x, y, w, RH(lbl_804CBC20), fl, &lbl_804CBC30, 0);
    Alpha(-3.0f);
    SPR(0x42);
    fn_801D620C(x + (w - RW(lbl_804CBCA0)) - 4, y, RW(lbl_804CBC40), RH(lbl_804CBC20), fl, &lbl_804CBC40, 0);
    Alpha(2.0f);
    SPR(0x4E);
    fn_801D620C(x + (w - RW(lbl_804CBCA0)), y + 3, RW(lbl_804CBCA0), RH(lbl_804CBCA0), fl, &lbl_804CBCA0, 0);
    Alpha(-1.0f);
}

void fn_801DA618(s16 x, s16 y, s16 w, u16 fl) {
    Alpha(0.1f);
    SPR(0x3E);
    fn_801D60D0(x - RW(lbl_804CBC20) + 4, y, RW(lbl_804CBC20), RH(lbl_804CBC20), fl, &lbl_804CBC20, 0);
    SPR(0x3F);
    fn_801D60D0(x + w - 4, y, RW(lbl_804CBC28), RH(lbl_804CBC28), fl, &lbl_804CBC28, 0);
    Alpha(-0.1f);
    SPR(0x41);
    fn_801D620C(x, y, w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    fn_801D620C(x, y + RH(lbl_804CBC20) - RH(lbl_804CBC38), w, RH(lbl_804CBC38), fl, &lbl_804CBC38, 0);
    Alpha(3.0f);
    SPR(0x40);
    fn_801D620C(x, y, w, RH(lbl_804CBC20), fl, &lbl_804CBC30, 0);
    Alpha(-3.0f);
}


extern void* lbl_804CBE08;

void fn_801D9E24(s16 x, s16 y, int sel, u16 fl) {
    Alpha(1.0f);
    SPR(0x4B);
    fn_801D60D0(x, y, RW(lbl_804CBC88), RH(lbl_804CBC88), fl, &lbl_804CBC88, 0);
    Alpha(-1.0f);
    if (sel != 0) {
        s16 w; s16 h; int y0; int x0; int y1; int x1;
        w = RW(lbl_804CBC88);
        h = RH(lbl_804CBC88);
        SPR(0x5F);
        y0 = y - 1;
        x0 = x - 1;
        fn_801D60D0(x0, y0, RW(lbl_804CBCD8), RH(lbl_804CBCD8), fl, &lbl_804CBCD8, 0);
        x1 = x + w;
        fn_801D60D0(x1 - RW(lbl_804CBCD8) + 1, y0, RW(lbl_804CBCD8), RH(lbl_804CBCD8), fl, &lbl_804CBCD8, 1);
        y1 = y + h;
        fn_801D60D0(x0, y1 - RH(lbl_804CBCD8) + 1, RW(lbl_804CBCD8), RH(lbl_804CBCD8), fl, &lbl_804CBCD8, 2);
        fn_801D60D0(x1 - RW(lbl_804CBCD8) + 1, y1 - RH(lbl_804CBCD8) + 1, RW(lbl_804CBCD8), RH(lbl_804CBCD8), fl, &lbl_804CBCD8, 3);
        SPR(0x60);
        fn_801D620C(x0 + RW(lbl_804CBCD8), y0, w - RW(lbl_804CBCD8) * 2 + 2, RH(lbl_804CBCE0), fl, &lbl_804CBCE0, 0);
        fn_801D620C(x0 + RW(lbl_804CBCD8), y1 + 1 - RH(lbl_804CBCE0), w - RW(lbl_804CBCD8) * 2 + 2, RH(lbl_804CBCE0), fl, &lbl_804CBCE0, 2);
        SPR(0x61);
        fn_801D620C(x0, y0 + RH(lbl_804CBCD8), RW(lbl_804CBCE8), h - RH(lbl_804CBCD8) * 2 + 2, fl, &lbl_804CBCE8, 0);
        fn_801D620C(x1 + 1 - RW(lbl_804CBCE8), y0 + RH(lbl_804CBCD8), RW(lbl_804CBCE8), h - RH(lbl_804CBCD8) * 2 + 2, fl, &lbl_804CBCE8, 1);
    }
}

#pragma use_lmw_stmw on
void fn_801DB770(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    int y2, x2;
    SPR(0x6E);
    fn_801D60D0(x, y, RW(lbl_804CBD00), RH(lbl_804CBD00), fl, &lbl_804CBD00, 0);
    x2 = x + w;
    fn_801D60D0(x2 - RW(lbl_804CBD00), y, RW(lbl_804CBD00), RH(lbl_804CBD00), fl, &lbl_804CBD00, 1);
    y2 = y + h;
    fn_801D60D0(x, y2 - RH(lbl_804CBD00), RW(lbl_804CBD00), RH(lbl_804CBD00), fl, &lbl_804CBD00, 2);
    fn_801D60D0(x2 - RW(lbl_804CBD00), y2 - RH(lbl_804CBD00), RW(lbl_804CBD00), RH(lbl_804CBD00), fl, &lbl_804CBD00, 3);
    SPR(0x6F);
    fn_801D620C(x + RW(lbl_804CBD00), y, w - RW(lbl_804CBD00) * 2, RH(lbl_804CBD00), fl, &lbl_804CBD08, 0);
    fn_801D620C(x + RW(lbl_804CBD00), y2 - RH(lbl_804CBD00), w - RW(lbl_804CBD00) * 2, RH(lbl_804CBD00), fl, &lbl_804CBD08, 2);
    SPR(0x70);
    fn_801D620C(x, y + RH(lbl_804CBD00), RW(lbl_804CBD00), h - RH(lbl_804CBD00) * 2, fl, &lbl_804CBD10, 0);
    fn_801D620C(x2 - RW(lbl_804CBD00), y + RH(lbl_804CBD00), RW(lbl_804CBD00), h - RH(lbl_804CBD00) * 2, fl, &lbl_804CBD10, 1);
    SPR(0x71);
    fn_801D620C(x + RW(lbl_804CBD00), y + RH(lbl_804CBD00), w - RW(lbl_804CBD00) * 2, h - RH(lbl_804CBD00) * 2, fl, &lbl_804CBD18, 0);
}

void fn_801DBA68(s16 x, s16 y, s16 w, s16 h, u8 a, u16 fl) {
    int y2, x2;
    Color c(0, 0, 0, a);
    SPR(0x81);
    fn_801D68E4(x, y, RW(lbl_804CBD88), RH(lbl_804CBD88), fl, &lbl_804CBD88, c, 0);
    x2 = x + w;
    fn_801D68E4(x2 - RW(lbl_804CBD88), y, RW(lbl_804CBD88), RH(lbl_804CBD88), fl, &lbl_804CBD88, c, 1);
    y2 = y + h;
    fn_801D68E4(x, y2 - RH(lbl_804CBD88), RW(lbl_804CBD88), RH(lbl_804CBD88), fl, &lbl_804CBD88, c, 2);
    fn_801D68E4(x2 - RW(lbl_804CBD88), y2 - RH(lbl_804CBD88), RW(lbl_804CBD88), RH(lbl_804CBD88), fl, &lbl_804CBD88, c, 3);
    SPR(0x82);
    fn_801D6BC0(x + RW(lbl_804CBD88), y, w - RW(lbl_804CBD88) * 2, RH(lbl_804CBD88), fl, &lbl_804CBD90, c, 0);
    fn_801D6BC0(x + RW(lbl_804CBD88), y2 - RH(lbl_804CBD88), w - RW(lbl_804CBD88) * 2, RH(lbl_804CBD88), fl, &lbl_804CBD90, c, 2);
    SPR(0x83);
    fn_801D6BC0(x, y + RH(lbl_804CBD88), RW(lbl_804CBD88), h - RH(lbl_804CBD88) * 2, fl, &lbl_804CBD98, c, 0);
    fn_801D6BC0(x2 - RW(lbl_804CBD88), y + RH(lbl_804CBD88), RW(lbl_804CBD88), h - RH(lbl_804CBD88) * 2, fl, &lbl_804CBD98, c, 1);
    SPR(0x84);
    fn_801D6BC0(x + RW(lbl_804CBD88), y + RH(lbl_804CBD88), w - RW(lbl_804CBD88) * 2, h - RH(lbl_804CBD88) * 2, fl, &lbl_804CBDA0, c, 0);
}
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




void fn_801DBDF0(s16 x, s16 y, u16 fl) {
    f32 s; int y2; int x2; void* st;
    st = fn_8007E4C4(&s);
    Alpha(3.0f);
    SPR(0x72);
    fn_801D620C(x, y, 0x260, RH(lbl_804CBD20), fl, &lbl_804CBD20, 0);
    fn_801D620C(x, y + RH(lbl_804CBD20), 0x260, RH(lbl_804CBD20), fl, &lbl_804CBD20, 2);
    Alpha(-0.1f);
    SPR(0x73);
    if (fn_801D09F0() != 0) {
        fn_801D620C(x + 0x33, y + 0x33, (s16)(0.7638191f * RW(lbl_804CBD28)), RH(lbl_804CBD28), fl, &lbl_804CBD28, 0);
    } else {
        fn_801D60D0(x + 0x33, y + 0x33, RW(lbl_804CBD28), RH(lbl_804CBD28), fl, &lbl_804CBD28, 0);
    }
    x += 0x69;
    y += 0x24;
    SPR(0x74);
    fn_801D60D0(x, y, RW(lbl_804CBD30), RH(lbl_804CBD30), fl, &lbl_804CBD30, 0);
    x2 = x + 0xB0;
    fn_801D60D0(x2 - RW(lbl_804CBD30), y, RW(lbl_804CBD30), RH(lbl_804CBD30), fl, &lbl_804CBD30, 1);
    y2 = y + 0x3A;
    fn_801D60D0(x, y2 - RH(lbl_804CBD30), RW(lbl_804CBD30), RH(lbl_804CBD30), fl, &lbl_804CBD30, 2);
    fn_801D60D0(x2 - RW(lbl_804CBD30), y2 - RH(lbl_804CBD30), RW(lbl_804CBD30), RH(lbl_804CBD30), fl, &lbl_804CBD30, 3);
    SPR(0x75);
    fn_801D620C(x + RW(lbl_804CBD30), y, 0xB0 - RW(lbl_804CBD30) * 2, RH(lbl_804CBD38), fl, &lbl_804CBD38, 0);
    fn_801D620C(x + RW(lbl_804CBD30), y2 - RH(lbl_804CBD38), 0xB0 - RW(lbl_804CBD30) * 2, RH(lbl_804CBD38), fl, &lbl_804CBD38, 2);
    SPR(0x76);
    fn_801D620C(x, y + RH(lbl_804CBD30), RW(lbl_804CBD40), 0x3A - RH(lbl_804CBD30) * 2, fl, &lbl_804CBD40, 0);
    fn_801D620C(x2 - RW(lbl_804CBD40), y + RH(lbl_804CBD30), RW(lbl_804CBD40), 0x3A - RH(lbl_804CBD30) * 2, fl, &lbl_804CBD40, 1);
    fn_8007E478(st, s);
}

extern u8 lbl_804CF7FF[8];
typedef unsigned long long u64;
u64 OSGetTime();
u64 fn_8028C418(u64, u64);
u64 fn_8028C634(u64, u64);
f64 fn_8028C764(u64);
f64 fn_80295940(f64);
void fn_80006B84(void*, void*, void*, int, int);
#define ALPHAQ(v) do { fn_8007E154(); fn_8007E720(v); fn_8007E164(); } while (0)

}
