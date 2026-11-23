/* Catmull-Rom interpolation between p1 and p2 at t (Hermite basis, tangents
   0.5*(p2-p0) and 0.5*(p3-p1)). Name guessed. Level: regs (float temporaries
   in other registers; same instruction order). */
#include "game/rA_800068A0/types.h"
f32 fn_8001EFE4(f32 p0, f32 p1, f32 p2, f32 p3, f32 t) {
    f32 h2 = (3.0f - 2.0f * t) * (t * t);
    f32 h1 = (2.0f * t + 1.0f) * ((t - 1.0f) * (t - 1.0f));
    f32 h3 = t * ((1.0f - t) * (1.0f - t));
    f32 h4 = t * ((t - 1.0f) * t);
    return h1 * p1 + h2 * p2 + h3 * (0.5 * (p2 - p0)) + h4 * (0.5 * (p3 - p1));
}
