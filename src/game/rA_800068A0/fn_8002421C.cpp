/* fn_8002421C: Sally menu step: if the pending command byte lbl_803CA870[0xC] is 0x81, jumps the proc to
   label 11; otherwise resumes the child proc, re-adds the help bar, refreshes and ends this proc.
   Exact (check_func.py --symbol-map fn_8002421C.symbols.json --strict-references). */
#include "game/rA_800068A0/types.h"
#include "game/helpbar.h"

extern "C" {
struct Mnu { u8 pad[0x50]; void* p50; };
extern char lbl_80361118[];
extern void* fn_801E5640(void*, int, int);
extern void fn_801E5448(void*, void*);
extern void fn_800893AC(void*);
extern void fn_80083B78(void*);
extern u32 lbl_803CA870[];
extern void fn_80083DC4(void*, int);
extern void fn_800231E4(void);
}

static inline void addHelp(Mnu* p) {
    HbHelpBar* b = new HbHelpBar(0x316);
    int one = 1;
    HbHelpBar* x;
    b->id = -0x1000;
    b->s.w[3] = one;
    b->a64 = lbl_80361118;
    b->flags |= 0x10;
    b->a60 = 0;
    b->a28 = 8;
    fn_801E5448(p, b);
    x = (HbHelpBar*)fn_801E5640(p, -0x1000, 0);
    if (x != 0) x->a60 = one;
}

extern "C" {
void fn_8002421C(Mnu* p) {
    switch (((u8*)lbl_803CA870)[0xC]) {
    case 0x81:
        fn_80083DC4(p, 0xB);
        break;
    default:
        fn_800893AC(p->p50);
        addHelp(p);
        fn_800231E4();
        fn_80083B78(p);
        break;
    }
}
}
