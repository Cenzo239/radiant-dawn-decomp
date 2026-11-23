/* Add a key to the running camera script, 80131294. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_80385E68[];
extern void* fn_80083B84(void*);
struct Ev { u8 kind; s16 key; Vec v; u32 d; };
struct Fx { u8 pad0[0x40]; Ev* ev; u8 n; };
static inline void AddEv(Fx* s, u8 k, int t, Vec v, u32 d) {
    s->ev[s->n].kind = k;
    s->ev[s->n].key = (f32)t / 16.666666f;
    s->ev[s->n].v = v;
    s->ev[s->n].d = d;
    s->n++;
}
static inline Vec MkV(f32 x, f32 y, f32 z) { Vec v; v.x = x; v.y = y; v.z = z; return v; }
void fn_80131294(u8 k, int t, u32 d, f32 x, f32 y, f32 z) {
    Fx* s = (Fx*)fn_80083B84(lbl_80385E68);
    if (s) {
        AddEv(s, k, t, MkV(x, y, z), d);
    }
}
}
