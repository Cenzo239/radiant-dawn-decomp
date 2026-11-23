/* fn_801D65EC (round 22, agent r22b): class `sched`, 2 words differ.
 * Draw a gradient-coloured textured quad: render flags fl|2, quad at (x, y) with the size of
 * src, corner colours g[0..3]; flip bit 0 mirrors horizontally (swapping the top colour
 * pair), bit 1 vertically (swapping the bottom pair), bits 8/9 call fn_80080690/fn_800806E0.
 * Built with tools/equiv/mkself.py from rR_80175E5C/fn_801D60D0.cpp and the fragment in
 * rR_80175E5C/wip/fn_801D60D0.cpp (no change needed).
 * Remaining: in the two colour swaps (std::swap with Color's self-checking assignment) the
 * `&a != &b` addresses are formed in the other order, and the four colour-argument
 * addresses for fn_80080940 are set up in the opposite order (same registers and values).
 * symcheck --anon --xargs: 27 blocks, 0 differ.
 */
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

void fn_801D60D0(int x, int y, int w, int h, int fl, Rect* src, int flip);

void fn_801D620C(int x, int y, int w, int h, int fl, Rect* src, int flip);

void fn_801D6388(int x, int y, int w, int h, int fl, const Color& c, int flip);

void fn_801D64AC(int x, int y, int fl, Rect* src, const Color& c, int flip);

void fn_801D68E4(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip);

void fn_801D6A4C(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip);

void fn_801D6BC0(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip);

void fn_801D6D68(int x, int y, int w, int h, int fl, Rect* src, const Color& c, int flip);


}
static inline void Swap(Color& a, Color& b) {
    u32 t = *(u32*)&a; /* the original copies a word here and bytes everywhere else */
    a = b;
    b = *(Color*)&t;
}

extern "C" {
void fn_801D6F1C(int x, int y, int w, int h, int fl, const Color& c);



}

/* ---- from build/tmp/r22b/fr_5ec.cpp ---- */
extern "C" {
extern "C" {
void fn_801D65EC(int x, int y, int fl, Rect* src, const Color* g, int flip) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    Color c0 = g[0];
    Color c1 = g[1];
    Color c2 = g[2];
    Color c3 = g[3];
    fn_800800D4(3);
    fn_80080388(x, y, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    if (flip & 1) {
        fn_80080494();
        Swap(c0, c1);
    }
    if (flip & 2) {
        fn_800804B4();
        Swap(c2, c3);
    }
    fn_80080578(0);
    if (flip & 0x100) fn_80080690();
    if (flip & 0x200) fn_800806E0();
    fn_80080940(c0, c1, c2, c3);
    fn_80080308();
}

}
}
