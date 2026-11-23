/* fn_8025F0E8 (0x7C): exact (round m8). Steps a linear fade and returns the current value (NW4R MoveValue-like:
 * counter, duration, current, origin, target).
 * Written on the fields directly, with the counter incremented after the interpolation; the earlier draft's
 * `int dur = f->dur; int t = f->t;` locals gave the same instructions with r0/r4/r5 rotated. */
#include "game/rN_8025EEF0/types.h"
extern "C" {
struct Fader {
    u8 pad[0x10];
    int t;     /* 0x10 */
    int dur;   /* 0x14 */
    f32 cur;   /* 0x18 */
    f32 from;  /* 0x1C */
    f32 to;    /* 0x20 */
};
f32 fn_8025F0E8(Fader* f);

f32 fn_8025F0E8(Fader* f) {
    if (f->t < f->dur) {
        f->cur = (f->to - f->from) * ((f32)f->t / (f32)f->dur) + f->from;
        f->t++;
    } else {
        f->cur = f->to;
    }
    return f->cur;
}
}
