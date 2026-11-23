/* fn_80025A74: exact (round 25). From equiv/fn_80025A74.cpp: the two objects are built by an inline derived constructor cD that first calls the base constructor cB (base vtable store, overwritten later), then sets the pointer and the derived vtable; statements in address order. */
/* Static initialiser of the pad unit (names guessed). Written as plain
   stores; the original is the compiler-generated __sinit of roughly

       static const void* const tbl148 = &lbl_80379230;   (five such pointers)
       static Derived obj160(&lbl_80379060);
       static const void* p168 = &lbl_80379078;
       static Derived obj170(&lbl_804CA068);

   where Derived (vtable lbl_80380360) derives from a base with vtable
   lbl_80383F28 and both keep one pointer at offset 0 with the vtable at 4.
   A port should use global definitions of that shape.
   Level: sched. One block; the original materialises lbl_80383F28 first and
   keeps lbl_80379230 in r31, ours the other way round, so the address-forming
   lis/addi/li lines sit in other slots. The twelve stores are in the same
   order. symcheck --anon: 1 block, 0 differ. */
#include "game/rA_800068A0/types.h"

struct Obj { void* p; void* vt; };

extern "C" {
extern u8 lbl_80383F28[];
extern u8 lbl_80380360[];
extern u8 lbl_80379060[];
extern u8 lbl_80379078[];
extern u8 lbl_803790D0[];
extern u8 lbl_80379128[];
extern u8 lbl_80379180[];
extern u8 lbl_803791D8[];
extern u8 lbl_80379230[];
extern u8 lbl_804CA068[8];
extern void* lbl_804CB148;
extern void* lbl_804CB14C;
extern void* lbl_804CB150;
extern void* lbl_804CB154;
extern void* lbl_804CB158;
extern Obj lbl_804CB160;
extern void* lbl_804CB168;
extern Obj lbl_804CB170;

static inline void cB(Obj* o) { o->vt = lbl_80383F28; }
static inline void cD(Obj* o, void* p) { cB(o); o->p = p; o->vt = lbl_80380360; }
void fn_80025A74(void) {
    lbl_804CB148 = lbl_80379230;
    lbl_804CB14C = lbl_803791D8;
    lbl_804CB150 = lbl_80379180;
    lbl_804CB154 = lbl_80379128;
    lbl_804CB158 = lbl_803790D0;
    cD(&lbl_804CB160, lbl_80379060);
    lbl_804CB168 = lbl_80379078;
    cD(&lbl_804CB170, lbl_804CA068);
}
}
