#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800614A8(RankData* g) {
    switch (g->b11) {
    case 0:
        g->b11 = 3;
        break;
    case 3:
        g->b11 = 1;
        break;
    case 1:
        g->b11 = 2;
        break;
    case 2:
        g->b11 = 0;
        g->h12++;
        if (g->h12 > 0x270f) {
            g->h12 = 0x270f;
        }
        break;
    }
}

extern "C" void fn_80061524(GameData* g) {
    g->t_a0 += fn_8017FA24();
    g->t_a8 += fn_8017FA24();
}

extern "C" void fn_80061584(GameData* g, u8 id) {
    if (g->b10 != id) {
        g->b10 = id;
        if (fn_8010B094(id)) {
            g->b92 = fn_80092E10(fn_8010B094(g->b10));
        }
    }
}
