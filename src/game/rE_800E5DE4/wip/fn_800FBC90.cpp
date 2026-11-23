/* 800FBC90: see the comment below. */
/* 2 words of 88: lwz u and lfs f scheduled the other way round. Writing u first moves u from r26 to r30. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct UData { u8 pad[0x10C]; u32 v10C; } UData;
typedef struct Rng { u8 pad[0x14]; int lo; int hi; } Rng;
typedef struct Mdl { u32 flags; u8 pad4[4]; GXColor c; u8 padC[0x4C]; f32 f58; u8 pad5C[0x28]; Rng* r; UData* u; } Mdl;
extern "C" {
extern u32 fn_8017FA1C(void);
extern void fn_80013C54(Mdl*, Rng*, void*, void*, void*);
extern void fn_800140A0(Mdl*, void*);
extern void fn_80013CF0(Mdl*, void*, void*);
extern void fn_800125A8(Mdl*, Rng*, void*, void*);
void fn_800FBC90(Mdl* m, void* b, void* c, void* d) {
    Rng* r = m->r;
    GXColor sv = m->c;
    f32 f = m->f58;
    UData* u = m->u;
    u32 range;
    if (r) {
        range = r->hi - r->lo;
        m->f58 = (int)(r->lo + fn_8017FA1C() % range);
    }
    if (u->v10C & 1) {
        m->c.r = 0x40;
        m->c.g = 0x40;
        m->c.b = 0x40;
    } else {
        m->c.r = 0x80;
        m->c.g = 0x80;
        m->c.b = 0x80;
    }
    fn_80013C54(m, r, b, c, d);
    fn_800140A0(m, b);
    fn_80013CF0(m, b, c);
    fn_800125A8(m, r, b, c);
    m->c = sv;
    m->f58 = f;
}
}
