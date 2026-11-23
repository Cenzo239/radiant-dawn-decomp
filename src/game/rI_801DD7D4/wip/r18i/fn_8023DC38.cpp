/* WIP (round 18): class `other`, 4 words: with `flags = 0` first (the original order) the zero and vtable registers and one `li` position differ. The r16i copy (vtable first) is at 1 word. */
/* fn_8023DC38: destructor of an archive/file entry (resets every field, optional delete). */
#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern u8 lbl_80390C58[];
void fn_80079210(void*);
static inline void feInit(FE* e) {
    e->flags = 0;
    e->vt = lbl_80390C58;
    e->name[0] = 0;
    e->a4b = -1;
    e->hash = 0;
    e->rc = 0;
    e->a56 = 2;
    e->parent = 0;
    e->data = 0;
    e->size = 0;
    e->pos = 0;
    e->a4 = 0;
    e->a8 = 0;
}
FE* fn_8023DC38(FE* e, int del) {
    if (e != NULL) {
        feInit(e);
        if (del > 0) fn_80079210(e);
    }
    return e;
}
}
