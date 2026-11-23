/* fn_801C3AB4 (0x7B4): functionally equal at `slots` level (tools/check_regs.py, round 21; 69 words differ).
 * New this round, written from the disassembly. Same instructions in the same order; the two int-to-float
 * conversion scratch doubles at 0x78/0x80(r1) are used in the opposite order from the original at each
 * conversion after the first two (the original gives the tile width 0x84 and the height 0x7C, ours the reverse).
 * symcheck.py --anon flags 8 of 64 blocks, all for that reason:
 *   - blocks 6, 8, 14, 18, 28, 39, 40, 41: "stack bytes differ at 0x7c..0x7f, 0x84..0x87" (the swapped scratch
 *     slots; they are dead after each conversion) and, following from it, the float argument numbering of the
 *     next call. Blocks 14/18 also list 0x90..0x97 / 0xb0..0xb7, the fctiwz scratch of the same statements.
 *   - (not flagged, but to know:) the two 9-float offset tables are copied from anonymous local templates here and from
 *     lbl_8036E0D0 / lbl_8036E0F4 in the original (values compared by hand: equal).
 * Notes for a port:
 *   - lbl_804CB9E8 (pulse, .sbss) and lbl_804CA8F8 (step, .sdata, initially 0.02f) are almost certainly
 *     function-local statics; they are externs here.
 *   - lbl_8036E118 + 0x94 is "%d" and + 0x214 is "/" (pooled strings of the translation unit).
 *   - `pi` is a local so the compiler doesn't fold 0.5f * pi; the original keeps it in f16 the same way.
 *   - The ring colour of passes 1..8 is {3g, 6g + 6, 12g + 6, 0xFF} with g the pulse value (0.5..1.0).
 */
/* fn_801C3AB4: draws the circular gauge "cur / max" (tile 0x17 as background, two numbers, then a ring of quads
 * from 0 to `v` in steps of max/18, drawn 9 times: once dark and 8 times offset by a pulsing glow). Names guessed. */
#pragma auto_inline off
#include "game/rF_8017F400/drawinl.h"
extern "C" {
extern double fn_80295534(double); /* cos */
extern double fn_80295940(double); /* sin */
extern void fn_80080538(f32, f32, f32, f32);
extern void fn_80080558(f32, f32, f32, f32);
extern f32 lbl_804CB9E8;      /* pulse value (function-local static in the original, most likely) */
extern f32 lbl_804CA8F8;      /* pulse step, starts at 0.02f */
void fn_801C3AB4(int max, f32 x, f32 y, f32 v);
}
static inline f32 Ang(f32 t, int max, f32 pi) { return 0.5f * pi + pi * (2.0f * (t / max)); }

void fn_801C3AB4(int max, f32 x, f32 y, f32 v) {
    char buf[16];
    GXColor2 col;
    int cur;
    int i;
    f32 sc;
    f32 t, dt;
    f32 cx, cy;
    f32 s0, c0, s1, c1;
    f32 a0, a1;
    f32 pi = 3.141592f;

    if (v < 0.0f) v = 0.0f;
    if (v > max) v = max;
    cur = v;
    Tile(1, 0xFF, 0x17, 0, x, y, 1.0f);
    SetScale(-0.01f);
    fn_80290DDC(buf, lbl_8036E118 + 0x94, cur);
    fn_800CB3A8(1.0f, 0.0f, 38.0f + x - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 28.0f + y, 1, 1, 0, buf);
    fn_800CB3A8(1.0f, 0.0f, 59.0f + x, 28.0f + y, 1, 1, 0, lbl_8036E118 + 0x214);
    fn_80290DDC(buf, lbl_8036E118 + 0x94, max);
    fn_800CB3A8(1.0f, 0.0f, 86.0f + x - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 28.0f + y, 0xC, 1, 0, buf);

    {
    f32 xs[9] = {0.0f, 0.0f, 3.0f, 0.0f, -3.0f, 0.0f, 6.0f, 0.0f, -6.0f};
    f32 ys[9] = {0.0f, 3.0f, 0.0f, -3.0f, 0.0f, 6.0f, 0.0f, -6.0f, 0.0f};
    lbl_804CB9E8 += lbl_804CA8F8;
    if (lbl_804CB9E8 >= 1.0f) {
        lbl_804CB9E8 = 1.0f;
        lbl_804CA8F8 = -0.02f;
    }
    if (lbl_804CB9E8 <= 0.5f) {
        lbl_804CB9E8 = 0.5f;
        lbl_804CA8F8 = 0.02f;
    }
    if (fn_801D09F0()) sc = 0.764f; else sc = 1.0f;
    if (max != 0) {
        dt = max / 18.0f;
        for (i = 0; i < 9; i++) {
            fn_8007E154();
            if (i == 0) fn_8007E174(0, 0x12); else fn_8007E174(0, 0x22);
            fn_8007E164();
            SetScale(-0.01f);
            cx = lbl_804CB9E8 * xs[i] + (62.0f + x);
            cy = lbl_804CB9E8 * ys[i] + (114.0f + y);
            for (t = 0.0f; t <= v; t += dt) {
                a0 = Ang(t, max, pi);
                if (t + dt <= v) a1 = Ang(t + dt, max, pi); else a1 = Ang(v, max, pi);
                s0 = fn_80295940(a0);
                c0 = -(f32)fn_80295534(a0);
                s1 = fn_80295940(a1);
                c1 = -(f32)fn_80295534(a1);
                if (i == 0) {
                    GXColor2 k = {0x00, 0x5A, 0x5A, 0x80};
                    col = k;
                } else {
                    f32 g = lbl_804CB9E8;
                    GXColor2 k = {(int)(3.0f * g), (int)(6.0f * g) + 6, (int)(12.0f * g) + 6, 0xFF};
                    col = k;
                }
                fn_800800D4(2);
                fn_80080348(sc * (c0 * 12.0f) + cx, cy - s0 * 12.0f, 0.0f, 0.0f);
                fn_80080538(sc * (c0 * 49.0f) + cx, cy - s0 * 49.0f, 0.0f, 0.0f);
                fn_80080558(sc * (c1 * 12.0f) + cx, cy - s1 * 12.0f, 0.0f, 0.0f);
                fn_80080368(sc * (c1 * 49.0f) + cx, cy - s1 * 49.0f, 0.0f, 0.0f);
                fn_80080508(col);
                fn_80080308();
            }
        }
    }
    }
    SetScale(0.11f);
}
