#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80061D98(GameData* g, u8 a, u8 b) {
    g->p955[g->n954].a = a;
    g->p955[g->n954].b = b;
    g->n954++;
}
