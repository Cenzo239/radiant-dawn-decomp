/* fn_8017B040 (0x120): exact (round m8). Screen filter fade process: optional wait, then fades the filter alpha from
 * `from` to `to` over `dur` frames and ends the process when it reached 0.
 * The counters are updated in place (`--o->wait`, `o->t++`); the earlier draft's `s16 w` / `u16 nt` helper locals
 * gave the same instructions with other volatile registers. */
#include "game/rR_80175E5C/types.h"
extern "C" {
struct Filter { u8 pad[0x26]; u8 a2; };
struct FadeIn {
    u8 pad0[0x30];
    Filter* f;  /* 0x30 */
    u16 t;      /* 0x34 */
    u16 dur;    /* 0x36 */
    u16 from;   /* 0x38 */
    u16 to;     /* 0x3A */
    u8 pad3C[2];
    s16 wait;   /* 0x3E */
};
void fn_8017B638(Filter* o);
void fn_80010788(int, int, void*, void*);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
void fn_80083B78(void*);
void fn_8017B040(FadeIn* o);

void fn_8017B040(FadeIn* o) {
    fn_80010788(3, 0x9C, fn_8017B638, o->f);
    if (o->wait > 0) {
        if (--o->wait == 0) {
            o->t = 0;
            o->dur = o->dur * 2;
            o->from = 0xFF;
            o->to = 0;
        }
    }
    if (o->t < o->dur) {
        o->t++;
        o->f->a2 = fn_8001EBC8(o->from, o->to, o->dur, o->t, 2);
    } else {
        o->f->a2 = o->to;
        if (o->to == 0) fn_80083B78(o);
    }
}
}
