/* near miss: fn_801CABAC, 10 lines: only f1/f2 swapped (x38 wants f1, the 1/64 constant f2). Statement orders, temporaries and inline helpers tried. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Q { u8 pad[0xA]; s16 xA; } Q;
typedef struct PP { u8 pad[0x30]; Q* q; u32 x34; f32 x38; u32 x3C; u32 x40; f32 x44; f32 x48; } PP;
void fn_801CABAC(PP* p) {
    p->x40 = 0;
    p->x44 = 0.015625f * p->q->xA;
    p->x48 = p->x38;
    if ((f32)__fabs(p->x44 - p->x48) > 180.0f) {
        if (p->x44 < p->x48) p->x44 += 360.0f;
        else if (p->x44 > p->x48) p->x48 += 360.0f;
    }
}
}
