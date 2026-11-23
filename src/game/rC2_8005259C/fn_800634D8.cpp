#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

static inline int rk(int v, u8* t) {
    int r = 0x45;
    if (v <= t[3]) {
        r = 0x44;
        if (v <= t[2]) {
            r = 0x43;
            if (v <= t[1]) {
                r = 0x42;
                if (v <= t[0]) {
                    r = 0x41;
                }
            }
        }
    }
    return r;
}
extern "C" int fn_800634D8(RankData* g) {
    if (g->b10 < 0x5a) {
        return 0x2d;
    }
    {
        u8* t = fn_8010B094(g->b10)->aA8;
        return rk(g->h12, t);
    }
}
