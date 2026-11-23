/* fn_8015F914 (round 24): AI driver step for the current unit. Exact once the first two tests are one
 * condition: `if (u->hp == 0 || (u->flags10C & 0x18)) return;` gives the original's `beq L; blr` for
 * the flag test (a separate `if` folds it into `bnelr`). */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

extern "C" {
extern u8 lbl_803CAB38[];
void fn_80083DC4(void* p, int label);

void fn_8015F914(void* p) {
    AiAct* act = &lbl_803CA870;
    Unit* u = act->unit;
    if (u->hp == 0 || (u->flags10C & 0x18)) return;
    if (u->flags10C & 1) return;
    if (lbl_803CAB38[0x11] != u->team[8]) {
        fn_800453B4(act, 1);
        return;
    }
    switch (act->action) {
    case 6:
    case 7:
    case 0x1C:
    case 0x1D:
    case 0x29:
    case 0x3D:
        (*(Unit***)&lbl_804183F0.res[0x85]) -= 1;
        u->w3B4 |= 0x4010000;
        fn_80083DC4(p, 1);
        return;
    default:
        u->w3B4 &= ~0x4000000;
        return;
    }
}
}
