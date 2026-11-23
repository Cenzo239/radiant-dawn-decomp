#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct Obj14 {
    u8 pad0[0x14];
    u8 b14;
    u8 b15;
    u8 b16;
    u8 b17;
} Obj14;
extern "C" void fn_80061A78(Obj14* p, u8 a, u8 b, u8 c, u8 d) {
    p->b14 = a;
    p->b15 = b;
    p->b16 = c;
    p->b17 = d;
}

static inline void pairAdd(GameData* g, u8 a, u8 b) {
    g->p955[g->n954].a = a;
    g->p955[g->n954].b = b;
    g->n954++;
}
extern "C" void fn_80061A8C(GameData* g, u8 a, u8 b) {
    g->n954 = 0;
    pairAdd(g, a, b);
}
