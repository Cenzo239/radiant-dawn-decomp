/* Window sheet sprite primitives. */
#include "game/rR_80175E5C/types.h"
extern "C" {
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_8041EF80[0x20];
}

extern "C" {
#define FLIP_TAIL(flip)             \
    if (flip & 1) fn_80080494();    \
    if (flip & 2) fn_800804B4();    \
    if (flip & 0x100) fn_80080690(); \
    if (flip & 0x200) fn_800806E0();

void fn_801D60D0(int x, int y, int w, int h, int fl, Rect* src, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E174(lbl_8041EF60, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080430(x, y, src->x0, src->y0, w, h);
    FLIP_TAIL(flip)
    fn_80080308();
}

void fn_801D620C(int x, int y, int w, int h, int fl, Rect* src, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E174(lbl_8041EF60, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080388(x, y, w, h);
    fn_800803C8(src->x0, src->y0, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    FLIP_TAIL(flip)
    fn_80080308();
}

void fn_801D6388(int x, int y, int w, int h, int fl, const Color& c, int flip) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080388(x, y, w, h);
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

void fn_801D64AC(int x, int y, int fl, Rect* src, const Color& c, int flip) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080388(x, y, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

void fn_801D68E4(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E174(lbl_8041EF60, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080430(x, y, src->x0, src->y0, w, h);
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

void fn_801D6A4C(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E244(lbl_8041EF60, lbl_8041EF80, 0, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080430(x, y, src->x0, src->y0, w, h);
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

void fn_801D6BC0(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E174(lbl_8041EF60, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080388(x, y, w, h);
    fn_800803C8(src->x0, src->y0, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

void fn_801D6D68(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip) {
    if (w == 0 || h == 0) return;
    fn_8007E154();
    fn_8007E244(lbl_8041EF60, lbl_8041EF80, 0, fl | 1);
    fn_8007E164();
    int mode = 1;
    if (flip & 0x300) mode = 2;
    fn_800800D4(mode);
    fn_80080388(x, y, w, h);
    fn_800803C8(src->x0, src->y0, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    FLIP_TAIL(flip)
    fn_80080508(c);
    fn_80080308();
}

}
static inline void Swap(Color& a, Color& b) {
    u32 t = *(u32*)&a; /* the original copies a word here and bytes everywhere else */
    a = b;
    b = *(Color*)&t;
}

extern "C" {


void fn_801D6F1C(int x, int y, int w, int h, int fl, const Color& c) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    fn_800800D4(4);
    fn_800803F0(0.5f + x, 0.5f + y, 0.5f + w, 0.5f + h);
    fn_80080508(c);
    fn_80080308();
}


}
