/* Gradient bar: fades in over 16 pixels and out over 16 */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

void fn_80080348(f32 x, f32 y, f32 u, f32 v);
void fn_80080368(f32 x, f32 y, f32 u, f32 v);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);

static const C4 k0 = {0x57, 0x49, 0x32, 0x00};
static const C4 k1 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k2 = {0x57, 0x49, 0x32, 0x00};
static const C4 k3 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k4 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k5 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k6 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k7 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k8 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k9 = {0x57, 0x49, 0x32, 0x00};
static const C4 k10 = {0x57, 0x49, 0x32, 0xFF};
static const C4 k11 = {0x57, 0x49, 0x32, 0x00};

static inline void grad(C4 a, C4 b, C4 c, C4 d) { fn_80080940(&a, &b, &c, &d); }

void fn_8028784C(f32 x, f32 y) {
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080348(x, y, 0.0f, 0.0f);
    fn_80080368(16.0f + x, 1.0f + y, 0.0f, 0.0f);
    grad(k0, k1, k2, k3);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(16.0f + x, y, 0.0f, 0.0f);
    fn_80080368(430.0f + x - 16.0f, 1.0f + y, 0.0f, 0.0f);
    grad(k4, k5, k6, k7);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(430.0f + x - 16.0f, y, 0.0f, 0.0f);
    fn_80080368(430.0f + x, 1.0f + y, 0.0f, 0.0f);
    grad(k8, k9, k10, k11);
    fn_80080578(0);
    fn_80080308();
}

}
