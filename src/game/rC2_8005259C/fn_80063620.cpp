/* Chapter grades: letters A..E as 0x41..0x45. */
#include "game/rC2_8005259C/base.h"
#pragma auto_inline off
struct CKind { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xec]; void* ec; u8 pf0[4]; CKind* f4; u8 pf8[0x10]; u64 flags; u8 p[0x386 - 0x110]; u16 h386; u8 pe[0x3f0 - 0x388]; };
struct ChapD { u8 pad[0x8f]; u8 b8f; u8 p90[0x14]; void* a4; u8 a8; u8 a9; u8 aa; u8 ab; u8 pac[4]; u8 b0, b1, b2, b3; };
struct GS { u8 pad[0x10]; u8 b10; u8 p11; s16 h12; };
extern "C" {
extern UX* lbl_804CB810;
extern GS lbl_803CAB38;
ChapD* fn_8010B094(u8);
void fn_8010E41C(void*, int);
u8 fn_80063568(GS*);
void* fn_8010B180(u8);
void fn_8011FF10(UX*, u8);
UX* fn_8012CE54(void*);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
static inline int rkLow(int v, ChapD* c) {
    int r = 0x45;
    if (v >= c->b3) {
        r = 0x44;
        if (v >= c->b2) {
            r = 0x43;
            if (v >= c->b1) {
                r = 0x42;
                if (v >= c->b0) {
                    r = 0x41;
                }
            }
        }
    }
    return r;
}
static inline int rkHigh(int v, ChapD* c) {
    int r = 0x45;
    if (v <= c->ab) {
        r = 0x44;
        if (v <= c->aa) {
            r = 0x43;
            if (v <= c->a9) {
                r = 0x42;
                if (v <= c->a8) {
                    r = 0x41;
                }
            }
        }
    }
    return r;
}
static inline u8 gradeTurns(GS* g) {
    if (g->b10 < 0x5a) {
        return 0x2d;
    }
    return rkHigh(g->h12, fn_8010B094(g->b10));
}

extern "C" u8 fn_80063620(GS* g) {
    int sum;
    u8 buf[0x10];
    int i;
    if (g->b10 < 0x5a) {
        return 0x2d;
    }
    sum = 0;
    fn_8010E41C(buf, 4);
    for (i = 1; i < 0xff; i++) {
        UX* u = unitAt(i);
        if (u->ec && buf[u->f4->b8]) {
            sum += u->h386;
        }
    }
    return rkLow(sum, fn_8010B094(g->b10));
}

extern "C" u8 fn_8006376C(GS* g) {
    int sum;
    if (g->b10 < 0x5a) {
        return 0x2d;
    }
    sum = 0x45 - gradeTurns(g);
    sum += 0x45 - fn_80063568(g);
    sum += 0x45 - fn_80063620(g);
    return 0x45 - sum / 3;
}

