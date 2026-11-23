#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct It { u8 p[0x1f]; u8 a1f; };
struct Sl { It* it; u32 b; };
struct Inv { u8 p[0x12c]; Sl s[18]; };
struct Wy { u8 p[0x50]; s16 a50; u8 p52[0xa]; Inv* a5c; };
static inline Sl* nth(Wy* o, int n) {
    Sl* s; int i;
    for (i = 0; i < 18; i++) {
        s = &o->a5c->s[i];
        if (s != NULL && s->it != NULL && s->it->a1f != 0) {
            if (n-- == 0) return s;
        }
    }
    return NULL;
}
Sl* fn_8022291C(Wy* o) {
    if (o->a50 < 0 || o->a50 > 5) return NULL;
    return nth(o, o->a50);
}
}
