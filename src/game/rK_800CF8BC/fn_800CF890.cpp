/* Round 23 (r23b), exact: fn_800CF890. From wip/r18_fn_800CF890.cpp: the constructors' dead base-class vtable store
   (`o->vt = 0;` in an inline base constructor, base vtable not in the DOL) makes each object address load before its
   vtable address, as in the original. Port: only the final stores matter. */
/* fn_800CF890: static initialiser that sets the vtables of two global objects (vptr at +0x44). */
#include "game/rK_800CF8BC/types.h"
extern "C" {
extern u8 lbl_80383A24[];
extern u8 lbl_803839D0[];
struct GObj44 { u8 pad[0x44]; void* vt; };
extern GObj44 lbl_803E7290;
extern GObj44 lbl_803E72D8;
static inline void Base(GObj44* o) { o->vt = 0; }
static inline void Ctor(GObj44* o, void* vt) { Base(o); o->vt = vt; }
void fn_800CF890() {
    Ctor(&lbl_803E7290, lbl_80383A24);
    Ctor(&lbl_803E72D8, lbl_803839D0);
}
}
