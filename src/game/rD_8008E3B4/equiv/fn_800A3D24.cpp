/* EQUIVALENT (register-only, round 19): fn_800A3D24 at regs level (18 words, volatile registers). Hand-written static initialiser. */
/* fn_800A3D24: static initialiser of the script command object lbl_803E50C0 and three table
   pointers (hand-written; the original is compiler-generated from constructors). */
#include "game/rD_8008E3B4/types.h"
extern "C" {
struct CmdObj { void* tbl; void* vt; u8 pad8[4]; u16 c; u16 e; };
extern CmdObj lbl_803E50C0;
extern char lbl_80383F28[], lbl_803820A8[], lbl_80382050[], lbl_80381FF8[], lbl_80381EA8[], lbl_80381F64[];
extern void* lbl_804CB638;
extern void* lbl_804CB640;
extern void* lbl_804CB648;
static inline void BaseCtor(CmdObj* o) { o->vt = lbl_80383F28; }
void fn_800A3D24(void) {
    BaseCtor(&lbl_803E50C0);
    lbl_804CB638 = lbl_803820A8;
    lbl_804CB640 = lbl_80382050;
    lbl_804CB648 = lbl_80381FF8;
    lbl_803E50C0.tbl = lbl_80381EA8;
    lbl_803E50C0.c = 0;
    lbl_803E50C0.e = 0x46;
    lbl_803E50C0.vt = lbl_80381F64;
}
}
