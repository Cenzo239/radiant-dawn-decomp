/* fn_801BE154 (line draw with a soft border): exact (round m25a). Written like the sibling fn_80186FA4 (no Body inline) with the
 * width and height as `f32 w, h;` locals computed after the swap. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080578(int);
extern void fn_80080308(void);
void fn_801BE154(f32 x0, f32 y0, f32 x1, f32 y1, const C4* c) {
    f32 w, h;
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    if (x0 > x1) {
        f32 ty, tx; tx = x0; ty = y0;
        x0 = x1; y0 = y1; x1 = tx; y1 = ty;
    }
    w = x1 - x0;
    h = y1 - y0;
    fn_800800D4(4);
    fn_80080388(x0 - 2.4f, y0, 4.8f + w, h);
    fn_800804D4(c->r, c->g, c->b, c->a >> 2);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x0, y0, w, h);
    fn_800804D4(c->r, c->g, c->b, c->a);
    fn_80080578(0);
    fn_80080308();
}
}
