#include "game/rI_801DD7D4/types.h"
struct LN { LN* prev; LN* next; void* val; };
struct O { u8 p[0x52]; s16 cur; u8 p54[0x1c]; u32 size; LN* prev; LN* next; };
static inline LN* adv(LN* p, int n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
extern "C" void* fn_801E7A28(O* o) {
    if (o->size == 0) return 0;
    if (o->cur < 0 || !(o->size > o->cur)) return 0;
    return adv(o->next, o->cur)->val;
}
