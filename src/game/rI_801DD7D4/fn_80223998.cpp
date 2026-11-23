#include "game/rI_801DD7D4/types.h"
extern "C" {
struct LN { LN* prev; LN* next; void* val; };
struct LO { u8 p[0x56]; s16 sel; u8 p58[0x1c]; u32 size; LN* prev; LN* next; };
static inline LN* adv(LN* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}

void* fn_80223998(LO* o) {
    if (o->size == 0) return NULL;
    if (o->sel < 0 || o->size <= o->sel) return NULL;
    return adv(o->next, (int)o->sel)->val;
}
}
