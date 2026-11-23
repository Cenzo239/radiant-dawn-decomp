#include "game/rI_801DD7D4/types.h"
extern "C" {
/* Point stored as u16 and read through (s16), which gives `lhz; extsh` after a copy. */
struct Pt { u16 x, y; };
struct Ps { s16 x, y; };
Pt fn_801E32C8(const Pt& a, const Ps& b) {
    Pt r = a;
    r.x = (s16)r.x + b.x;
    r.y = (s16)r.y + b.y;
    return r;
}
}
