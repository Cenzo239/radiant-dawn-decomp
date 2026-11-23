#include "game/rG_800A3D88/chr.h"

extern "C" {

struct Eff {
    u8 pad[0x38];
    void* m38;
};

int fn_800C09E0(Eff*, int);

struct ChrE {
    u8 pad[0x3C];
    Eff* e[2];
};

/* Finds the first effect slot in state != 0xF; self-recursion unrolled by the inliner. */
#pragma push
#pragma inline_depth(3)
#pragma use_lmw_stmw on
Eff* fn_800B5784(ChrE* c, int i) {
    if (i < 0) {
        for (int j = 0; j < 2; j++) {
            Eff* x = fn_800B5784(c, j);
            if (x != NULL && x->m38 != NULL && fn_800C09E0(x, -1) != 0xF) {
                return x;
            }
        }
        return NULL;
    }
    return c->e[i];
}
#pragma pop

} // extern "C"
