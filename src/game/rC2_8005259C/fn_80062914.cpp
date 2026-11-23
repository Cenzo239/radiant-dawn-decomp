#include "game/rC2_8005259C/base.h"
struct CKind { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xec]; void* ec; u8 pf0[4]; CKind* f4; u8 pf8[0x386 - 0xf8]; u16 h386; u8 pe[0x3f0 - 0x388]; };
extern "C" {
extern UX* lbl_804CB810;
extern int lbl_804CA378;
void* memset(void*, int, u32);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

extern "C" UX* fn_80062914(void* g) {
    UX* best = 0;
    int top = 0;
    u8 mask[0x10];
    u8 ids[7] = {0x00, 0x05, 0x07, 0x08, 0x09, 0x0a, 0xff};
    u8* p;
    int i;
    memset(mask, (u8)lbl_804CA378, 0xb);
    {
        u8 c;
        p = ids;
        while ((c = *p) != 0xff) {
            mask[c] = 1;
            p++;
        }
    }
    for (i = 1; i < 0xff; i++) {
        UX* u = unitAt(i);
        if (u->ec && mask[u->f4->b8]) {
            if (top < u->h386) {
                top = u->h386;
                best = u;
            }
        }
    }
    return best;
}
