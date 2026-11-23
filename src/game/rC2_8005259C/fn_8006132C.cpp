#include "game/rC2_8005259C/base.h"
struct CK { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xe8]; UX* next; void* ec; u8 pf0[4]; CK* f4; u8 pf8[0x10]; u64 flags; u8 p[0x386 - 0x110]; u16 h386; u8 pe[0x3f0 - 0x388]; };
struct UL { u8 pad[0x48]; UX* h48; };
extern "C" {
extern UX* lbl_804CB810;
extern UL* lbl_804CB814;
extern int lbl_804CA378;
void* memset(void*, int, u32);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

extern "C" void fn_8006132C(void) {
    u8 mask[0x10];
    u8 ids[8] = {0x0, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xff};
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
            u->h386 = 0;
        }
    }
    {
        UX* n;
        UX* v = lbl_804CB814->h48;
        while (v) {
            n = v->next;
            v->flags &= ~0x8000ULL;
            v = n;
        }
    }
}
