/* fn_80023E2C: Sally menu step: re-adds the help bar (0x68 widget, id -0x1000, line 2 on), resumes the
   child proc in p50 and ends this proc.
   Exact (check_func.py --symbol-map fn_80023E2C.symbols.json --strict-references). */
#include "game/rA_800068A0/types.h"
#include "game/helpbar.h"

extern "C" {
struct Mnu { u8 pad[0x50]; void* p50; };
extern char lbl_80361118[];
extern void* fn_801E5640(void*, int, int);
extern void fn_801E5448(void*, void*);
extern void fn_800893AC(void*);
extern void fn_80083B78(void*);

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
void fn_80023E2C(Mnu* p) {
    addHelp(p);
    fn_800893AC(p->p50);
    fn_80083B78(p);
}
}
