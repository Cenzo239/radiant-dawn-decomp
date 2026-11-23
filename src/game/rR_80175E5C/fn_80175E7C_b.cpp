/* fn_80175E7C: exact (round 18). File name has _b because fn_80175E7C.cpp is the older multi-function file. */
/* fn_80175E7C: linear blend of two RGBA colours by k clamped to 0..1; the result is returned as one word. */
#include "game/rR_80175E5C/types.h"
struct C4 { u8 r, g, b, a; };
extern "C" {
f32 fn_8001EF30(f32, f32, f32, f32);
u32 fn_80175E7C(
#if TARGET_PC
fe10_rgba fromv, fe10_rgba tov, f32 k
#else
C4* from, C4* to, f32 k
#endif
) {
#if TARGET_PC
    C4* from = (C4*)&fromv;
    C4* to = (C4*)&tov;
#endif
    C4 c;
    if (k < 0.0f) {
        k = 0.0f;
    }
    if (k > 1.0f) {
        k = 1.0f;
    }
    c.r = (int)fn_8001EF30(from->r, to->r, 1.0f, k);
    c.g = (int)fn_8001EF30(from->g, to->g, 1.0f, k);
    c.b = (int)fn_8001EF30(from->b, to->b, 1.0f, k);
    c.a = (int)fn_8001EF30(from->a, to->a, 1.0f, k);
    return *(u32*)&c;
}
}
