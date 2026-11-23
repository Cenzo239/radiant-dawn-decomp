/* fn_801CABAC (0x8C): exact (round m8). Starts a turn from the stored angle x38 to the target's angle (s16, 1/64
 * degree units), going the short way round.
 * Both float helpers are inline functions: the angle conversion and fabsf. Their return values are separate
 * temporaries, which gives the original float registers (x38 f1, 1/64 f2, product f3); written in place
 * (`0.015625f * p->q->xA`, `(f32)__fabs(a - b)`) the same instructions come out with f1/f2 exchanged. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Q { u8 pad[0xA]; s16 xA; } Q;
typedef struct PP { u8 pad[0x30]; Q* q; u32 x34; f32 x38; u32 x3C; u32 x40; f32 x44; f32 x48; } PP;
void fn_801CABAC(PP* p);

static inline f32 fabsf_(f32 x) { return (f32)__fabs(x); }
static inline f32 Deg(s16 a) { return 0.015625f * a; }

void fn_801CABAC(PP* p) {
    p->x40 = 0;
    p->x44 = Deg(p->q->xA);
    p->x48 = p->x38;
    if (fabsf_(p->x44 - p->x48) > 180.0f) {
        if (p->x44 < p->x48) p->x44 += 360.0f;
        else if (p->x44 > p->x48) p->x48 += 360.0f;
    }
}
}
