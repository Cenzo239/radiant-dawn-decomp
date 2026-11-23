/* fn_80134ECC (0xC4): exact (round m12). Draws every visible mesh whose group flags match, in three passes.
   From equiv/fn_80134ECC.cpp. Lever: no inline and no block-local declarations; every local is declared at
   the top of the function with the short-lived temporaries (g, gr, m, fl) BEFORE the loop counters. That puts
   k/kk/i in r31/r30/r29 above the saved parameters (r28..r26) and gives fl/m/gr r5/r4/r3. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8001A218(int, void*);
void fn_80134ECC(MapModel* mm, u32 need, u32 reject) {
    u32 g;
    MapGroup* gr;
    Mesh* m;
    u8 fl;
    int k;
    int kk;
    int i;
    if (mm->flags & 0x40000000) {
        for (k = 0; k < 3; k++) {
            kk = k + 1;
            for (i = 0; i < mm->nMesh; i++) {
                fl = mm->mesh[i].flags;
                m = &mm->mesh[i];
                gr = m->group;
                if (!(fl & 4) && !(fl & 0x40) && !(fl & 0x20)) {
                    g = gr->flags;
                    if (!(g & reject) && (need == 0 || need == (need & g))) fn_8001A218(kk, (u8*)m + 0x14);
                }
            }
        }
    }
}
}
