/* Ally pair list queries and add, 80112F64..801131D8. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
struct PairEnt { void* a; void* b; u8 c; u8 d; };
extern PairEnt* lbl_804CB7E4;
extern PairEnt lbl_803EC418[];
extern int lbl_804CB800;
struct UnitH { u8 pad0[0xEC]; void* ec; };
int fn_80112F64(UnitH* u) {
    int n = 0;
    {
        PairEnt* e;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                n++;
            }
        }
    }
    {
        int i;
        for (i = 0; i < lbl_804CB800; i++) {
            if (lbl_803EC418[i].c == 1 && (u->ec == lbl_803EC418[i].a || u->ec == lbl_803EC418[i].b)) {
                n++;
            }
        }
    }
    return n;
}
void* fn_80112FFC(UnitH* u, int k) {
    PairEnt* e;
    int n;
    PairEnt* g;
    int i;
    void* p;
    void* x;
    n = 0;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                if (k == n++) {
                    if (u->ec == e->a) {
                        return e->b;
                    }
                    return e->a;
                }
            }
        }
        g = lbl_803EC418;
        for (i = 0; i < lbl_804CB800; i++, g++) {
            if (g->c == 1) {
              x = g->a; p = u->ec;
              if (p == x || p == g->b) {
                if (k == n++) {
                    if (p == x) { return g->b; }
                    return x;
                }
              }
            }
        }
    return 0;
}
void fn_801130D4(void* a, void* b, u32 c, u8 d) {
    int n;
    int found = 0;
    {
        PairEnt* e;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == c) {
                if ((a == e->a && b == e->b) || (a == e->b && b == e->a)) {
                    found = 1;
                    break;
                }
            }
        }
    }
    n = lbl_804CB800;
    {
        int i; PairEnt* g = lbl_803EC418;
        for (i = 0; !found && i < n; i++) {
            PairEnt* h=&lbl_803EC418[i];
            if (h->c == c) {
                if ((a == h->a && b == h->b) || (a == h->b && b == h->a)) {
                    found = 1;
                    break;
                }
            }
        }
    }
    if (!found && n < 0x60) {
        PairEnt* e = &lbl_803EC418[n];
        e->a = a;
        e->b = b;
        e->c = c;
        e->d = d;
        lbl_804CB800++;
    }
}
}
