#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(int, int);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080578(int);
extern void fn_80080308(void);
static inline void Body(f32 x0, f32 y0, f32 x1, f32 y1, const C4* c) {
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    if (x0 > x1) {
        f32 ty, tx; tx = x0; ty = y0;
        x0 = x1; y0 = y1; x1 = tx; y1 = ty;
    }
    x1 -= x0;
    y1 -= y0;
    fn_800800D4(4);
    fn_80080388(x0 - 2.4f, y0, 4.8f + x1, y1);
    fn_800804D4(c->r, c->g, c->b, c->a >> 2);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x0, y0, x1, y1);
    fn_800804D4(c->r, c->g, c->b, c->a);
    fn_80080578(0);
    fn_80080308();
}
void fn_801BE154(f32 x0, f32 y0, f32 x1, f32 y1, const C4* c) { Body(x0, y0, x1, y1, c); }
}
