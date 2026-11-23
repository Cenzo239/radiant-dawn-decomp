#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern u8 lbl_80390C58[];
void fn_80079210(void*);
static inline void feInit(FE* e) {
    e->vt = lbl_80390C58;
    e->flags = 0;
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
