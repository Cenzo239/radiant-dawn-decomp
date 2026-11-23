#include "game/rI_801DD7D4/types.h"
struct Pt { s16 x, y; };
struct Pu { u16 x, y; };
struct W;
extern "C" {
Pu fn_801E32C8(const Pu& a, const Pt& b) {
    Pu r = a;
    r.x = (s16)r.x + b.x;
    r.y = (s16)r.y + b.y;
    return r;
}
}
struct W { u8 p[0xa]; Pu pos; u8 pe[4]; Pt ofs; u8 p16[0x3c-0x16]; W* parent; };
static inline Pu gp(const W* o) { Pu p; p.x = o->pos.x; p.y = o->pos.y; return p; }
static inline void gp2(Pu& p, const W* o) { p.x = o->pos.x; p.y = o->pos.y; }
#pragma use_lmw_stmw on
#pragma push
#pragma inline_depth(3)
extern "C" Pu* fn_801E2204(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) fn_801E2204(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
    return out;
}
#pragma pop
