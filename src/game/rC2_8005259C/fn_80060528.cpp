#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80060528(Entry16* t, int i, u8* a, u16* b, u32* c) {
    *a = t[i].b0;
    *b = t[i].h2;
    *c = t[i].w4;
}

extern "C" void fn_8006054C(Entry16b* t, int i, u8* a, u16* b, u32* c, s16* d, u32* e) {
    *a = t[i].b0;
    *b = t[i].h2;
    *c = t[i].w4;
    *d = t[i].h8;
    *e = t[i].wc;
}
