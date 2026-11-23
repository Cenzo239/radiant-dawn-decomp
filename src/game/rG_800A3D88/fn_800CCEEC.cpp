/* fn_800CCEEC: exact (round 18). Static initialiser written out by hand (BaseCtor stands for the base class constructor). */
/* fn_800CCEEC: static initialiser for two global objects with a common base (vptr, one zeroed word);
   each gets its base vtable, then its own, and is registered for destruction. */
#include "game/rG_800A3D88/types.h"
extern "C" {
struct GBase { void* vt; int x; };
extern GBase lbl_804CB6E0;
extern GBase lbl_804CB6E8;
extern u8 lbl_80383024[];
extern u8 lbl_803830BC[];
extern u8 lbl_80383070[];
extern u8 lbl_803E7278[];
extern u8 lbl_803E7284[];
void fn_800CCF84(void*, int);
void fn_800CCFF8(void*, int);
void __register_global_object(void*, void*, void*);
static inline void BaseCtor(GBase* o) { o->vt = lbl_80383024; o->x = 0; }
void fn_800CCEEC() {
    BaseCtor(&lbl_804CB6E0);
    lbl_804CB6E0.vt = lbl_803830BC;
    __register_global_object(&lbl_804CB6E0, fn_800CCF84, lbl_803E7278);
    BaseCtor(&lbl_804CB6E8);
    lbl_804CB6E8.vt = lbl_80383070;
    __register_global_object(&lbl_804CB6E8, fn_800CCFF8, lbl_803E7284);
}
}
