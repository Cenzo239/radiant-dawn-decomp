/* fn_800CF890 (round 18): NOT at regs level. 11 instructions, same code, but the compiler loads each vtable address
   before its object address (the original does the reverse), so the reference check fails. Four spellings tried. */
/* fn_800CF890: static initialiser that sets the vtables of two global objects (vptr at +0x44). */
#include "game/rK_800CF8BC/types.h"
extern "C" {
extern u8 lbl_80383A24[];
extern u8 lbl_803839D0[];
struct GObj44 { u8 pad[0x44]; void* vt; };
extern GObj44 lbl_803E7290;
extern GObj44 lbl_803E72D8;
void fn_800CF890() {
    GObj44* a = &lbl_803E7290;
    GObj44* b = &lbl_803E72D8;
    a->vt = lbl_80383A24;
    b->vt = lbl_803839D0;
}
}
