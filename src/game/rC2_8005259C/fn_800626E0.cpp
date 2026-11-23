#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_800626E0(RankData* g) {
    u8 k = fn_8010B094(g->b10)->b89;
    int r = 0;
    switch (k) {
    case 0:
        r = g->w18;
        break;
    case 1:
        r = g->w1c;
        break;
    case 2:
        r = g->w20;
        break;
    case 3:
        r = g->w1c + g->w20;
        break;
    case 4:
        r = g->w18 + g->w1c;
        r += g->w20;
        break;
    }
    return r;
}
