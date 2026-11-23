#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);
void* fn_801E40B0(void*, int);

typedef struct Tgt {
    u8 pad0[0x12];
    s16 x12, x14, x16, x18;
    u8 pad1a[0x50 - 0x1a];
    u8 x50;
    u8 pad51[0x70 - 0x51];
    s16 x70, x72;
    u8 pad74[0x7c - 0x74];
    s16 x7c, x7e;
    u8 pad80[0x84 - 0x80];
    s16 x84, x86;
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

void fn_801F0684(Tw* o) {
    Tgt* t = twBack(o);
    t->x50 = 0;
    t->x70 = 0;
    t->x72 = 0;
    if (o != NULL) {
        fn_801E40B0(o, 0);
    }
}

void fn_801F06C4(Tw* o) { o->x40 = 0; }

void fn_801F0E14(Tw* o) {
    Tgt* t = twBack(o);
    t->x50 = 0;
    t->x7c = 0;
    t->x7e = 0;
    if (o != NULL) {
        fn_801E40B0(o, 0);
    }
}

void fn_801F0E54(Tw* o) { o->x40 = 0; }

}
