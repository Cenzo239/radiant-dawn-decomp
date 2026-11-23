/* fn_80134ECC: functionally equal (regs level per tools/check_regs.py; registers differ from the original).  */
/* Draw every visible mesh whose group flags match, in three passes. From wip/near2.cpp. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8001A218(int, void*);
static inline void DrawAll(MapModel* mm, u32 need, u32 reject) {
    /*P*/
    int k;
    int kk;
    int i;
    /*E*/
    if (mm->flags & 0x40000000) {
        for (k = 0; k < 3; k++) {
            kk = k + 1;
            for (i = 0; i < mm->nMesh; i++) {
                MapGroup* gr;
                u8 fl = mm->mesh[i].flags;
                Mesh* m = &mm->mesh[i];
                gr = m->group;
                if (!(fl & 4) && !(fl & 0x40) && !(fl & 0x20)) {
                    u32 g = gr->flags;
                    if (!(g & reject) && (need == 0 || need == (need & g))) fn_8001A218(kk, (u8*)m + 0x14);
                }
            }
        }
    }
}
void fn_80134ECC(MapModel* mm, u32 need, u32 reject) { DrawAll(mm, need, reject); }

}
