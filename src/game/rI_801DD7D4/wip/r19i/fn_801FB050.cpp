/* WIP (round 19): class `other`, 40 of 43 instructions, complete and believed correct. Left: the second
   test is `li r0,0; srawi r0,r0,31; rlwinm r3,r3,0,29,29; or. r0,r3,r0` in the original (the only place
   in the DOL): a 64-bit compare of the masked low word with a sign-extended int 0. Ours folds it to one
   `rlwinm.`; 12 spellings tried. */
/* fn_801FB050: TRUE for a held item that is neither locked/equipped-only (item flag 0x20000 or the
   inventory entry's 0x10 bit) nor flagged 4 in its item data: i.e. an item that may be handed over. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
struct Inv { int id; u8 b4; u8 b0 : 3; u8 bit10 : 1; u8 b4_ : 4; };
extern "C" {
u64* fn_801116B8(Inv*);
BOOL fn_801FB050(Inv* e) {
    BOOL r;
    BOOL t;
    if (e == NULL || e->id == 0) return FALSE;
    r = FALSE;
    t = TRUE;
    if ((*(u32*)fn_801116B8(e) & 0x20000) == 0 && e->bit10 == 0) t = FALSE;
    if (!t) {
        if ((*fn_801116B8(e) & 4) == 0) r = TRUE;
    }
    return r;
}
}
