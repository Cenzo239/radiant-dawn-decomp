/* Slide tweens: mode bits pick a direction, the target's offset eases over o->x42 frames.
   The same step exists for four offset fields in both directions. Round 7. */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);

typedef struct Tgt {
    u8 pad0[0x12];
    s16 x12, x14, x16, x18;
    u8 pad1a[0x70 - 0x1a];
    s16 x70, x72;
    u8 pad74[0x7c - 0x74];
    s16 x7c, x7e;
    u8 pad80[0x84 - 0x80];
    s16 x84, x86;
    u8 pad88[0x94 - 0x88];
    s16 x94, x96;
} Tgt;

typedef struct Tw {
    u8 pad[0x34];
    RList list;
    s16 x40, x42;
    int x44;
    int x48;
} Tw;

static inline Tgt* twBack(Tw* o) {
    return o->list.size != 0 ? (Tgt*)o->list.prev->val : NULL;
}

static inline s16 tgtW(Tgt* t) { return t->x16 - t->x12; }
static inline s16 tgtH(Tgt* t) { return t->x18 - t->x14; }

/* b must be assigned through if/else: a ternary or inline result takes r31 ahead of dur and dy. */
#define SLIDE_IN(fn, fx, fy) \
void fn(Tw* o) { \
    int dur; int dy; Tgt* b; int dx; \
    if (o->list.size != 0) b = (Tgt*)o->list.prev->val; else b = NULL; \
    dx = 0; \
    dur = o->x42; \
    dy = 0; \
    switch (o->x48) { \
    case 1: \
        dx = tgtW(twBack(o)); \
        break; \
    case 2: \
        dx = -tgtW(twBack(o)); \
        break; \
    case 8: \
        dy = tgtH(twBack(o)); \
        break; \
    case 4: \
        dy = -tgtH(twBack(o)); \
        break; \
    } \
    if (o->x40 >= (s16)dur) { \
        fn_80083B78(o); \
    } else { \
        int z = 0; \
        int x, y; \
        o->x40++; \
        x = (int)fn_8017F68C(2, z, (s16)dx, o->x40, (s16)dur); \
        y = (int)fn_8017F68C(2, z, (s16)dy, o->x40, (s16)dur); \
        b->fx = x; \
        b->fy = y; \
    } \
}
#define SLIDE_OUT(fn, fx, fy) \
void fn(Tw* o) { \
    int dur; int dy; Tgt* b; int dx; \
    if (o->list.size != 0) b = (Tgt*)o->list.prev->val; else b = NULL; \
    dx = 0; \
    dur = o->x42; \
    dy = 0; \
    switch (o->x48) { \
    case 1: \
        dx = -tgtW(twBack(o)); \
        break; \
    case 2: \
        dx = tgtW(twBack(o)); \
        break; \
    case 8: \
        dy = -tgtH(twBack(o)); \
        break; \
    case 4: \
        dy = tgtH(twBack(o)); \
        break; \
    } \
    if (o->x40 >= (s16)dur) { \
        fn_80083B78(o); \
    } else { \
        int z = 0; \
        int x, y; \
        o->x40++; \
        x = (int)fn_8017F68C(5, (s16)dx, z, o->x40, (s16)dur); \
        y = (int)fn_8017F68C(5, (s16)dy, z, o->x40, (s16)dur); \
        b->fx = x; \
        b->fy = y; \
    } \
}
SLIDE_IN(fn_801EFF40, x84, x86)
SLIDE_OUT(fn_801F044C, x84, x86)
SLIDE_IN(fn_801F06D0, x70, x72)
SLIDE_OUT(fn_801F0BDC, x70, x72)
SLIDE_IN(fn_801F0E60, x7c, x7e)
SLIDE_OUT(fn_801F136C, x7c, x7e)
SLIDE_IN(fn_80200064, x94, x96)
SLIDE_OUT(fn_80200570, x94, x96)
}
