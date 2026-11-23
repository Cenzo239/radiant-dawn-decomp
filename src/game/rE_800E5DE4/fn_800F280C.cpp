#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
extern "C" {
extern void fn_800F22E8(int, int, GXColor, void*);
extern void fn_800F2B04(int, int, void*, GXColor, void*);
void fn_800F280C(GXColor col, void* p, f32 x, f32 y) {
/*P*/
    f32 fx;
    f32 fy;
    int ix;
    int iy;
/*E*/
    ix = x;
    iy = y;
    fx = x - (int)x;
    fy = y - (int)y;
    fn_800F22E8(ix, iy, col, p);
    if (fx < 0.3f) {
        fn_800F22E8(ix - 1, iy, col, p);
        if (fy < 0.3f) fn_800F22E8(ix - 1, iy - 1, col, p);
        if (fy > 0.7f) fn_800F22E8(ix - 1, iy + 1, col, p);
    }
    if (fx > 0.7f) {
        fn_800F22E8(ix + 1, iy, col, p);
        if (fy < 0.3f) fn_800F22E8(ix + 1, iy - 1, col, p);
        if (fy > 0.7f) fn_800F22E8(ix + 1, iy + 1, col, p);
    }
    if (fy < 0.3f) fn_800F22E8(ix, iy - 1, col, p);
    if (fy > 0.7f) fn_800F22E8(ix, iy + 1, col, p);
}
void fn_800F3050(void* a, GXColor col, void* p, f32 x, f32 y) {
/*P*/
    f32 fx;
    f32 fy;
    int ix;
    int iy;
/*E*/
    ix = x;
    iy = y;
    fx = x - (int)x;
    fy = y - (int)y;
    fn_800F2B04(ix, iy, a, col, p);
    if (fx < 0.45f) {
        fn_800F2B04(ix - 1, iy, a, col, p);
        if (fy < 0.45f) fn_800F2B04(ix - 1, iy - 1, a, col, p);
        if (fy > 0.55f) fn_800F2B04(ix - 1, iy + 1, a, col, p);
    }
    if (fx > 0.55f) {
        fn_800F2B04(ix + 1, iy, a, col, p);
        if (fy < 0.45f) fn_800F2B04(ix + 1, iy - 1, a, col, p);
        if (fy > 0.55f) fn_800F2B04(ix + 1, iy + 1, a, col, p);
    }
    if (fy < 0.45f) fn_800F2B04(ix, iy - 1, a, col, p);
    if (fy > 0.55f) fn_800F2B04(ix, iy + 1, a, col, p);
}
}
