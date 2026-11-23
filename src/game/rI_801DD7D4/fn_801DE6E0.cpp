#include "game/rI_801DD7D4/types.h"
#pragma use_lmw_stmw on
struct Ls { u8 p[0x40]; u8 ids[0x64]; s8 n; };
struct Sp { u8 p[0x30]; s16 x, y; };
extern "C" Sp* fn_80085EF8(u8);
struct BD { int x0; };
class G : public BD { public: virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual int bx(); virtual int by(); virtual void v50(); virtual void v54(); virtual int cw(); virtual int ch(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual int ox(); virtual int oy(); virtual int rows(struct Ls*); virtual int cols();  };
extern "C" void fn_801DE6E0(G* g, Ls* a) {
/*P*/
    s16 x0;
    s16 y0;
    int r;
    int k;
    int c;
    int cw;
    int ch;
    int nr;
    int nc;
/*E*/
    cw = g->cw();
    ch = g->ch();
    x0 = g->bx() + g->ox();
    y0 = g->by() + g->oy();
    nr = g->rows(a);
    nc = g->cols();
    r = 0;
    k = 0;
    for (; r < (s16)nr && k < a->n; r++) {
        for (c = 0; c < (s16)nc && k < a->n; c++, k++) {
            Sp* s = fn_80085EF8(a->ids[k]);
            s->x = x0 + c * (s16)cw;
            s->y = y0 + r * (s16)ch;
        }
    }
}
