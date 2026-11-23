/* fn_801F17C4: builds the help bar (0x68 widget, id -0x1000) of the unit-list screen, enables its second
   line in the two special modes and clears the shared selection word.
   Exact (check_func.py --symbol-map fn_801F17C4.symbols.json --strict-references): needs the real class
   hierarchy in game/helpbar.h. */
#include "game/rI_801DD7D4/types.h"
#include "game/helpbar.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8036F03C[];
extern int lbl_803CA870[];
int fn_80058718(void);
int fn_8002460C(void);
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
}
extern "C" void fn_801F17C4(void* s) {
    HbHelpBar* b = new HbHelpBar;
    int one = 1;
    b->id = -0x1000;
    b->s.w[3] = one;
    b->a64 = lbl_8036F03C;
    b->flags |= 0x10;
    b->a60 = 0;
    b->a28 = 8;
    fn_801E5448(s, b);
    if (fn_80058718() != 0 && fn_8002460C() != 0) {
        HbHelpBar* h = (HbHelpBar*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = one;
    }
    lbl_803CA870[1] = 0;
    if (fn_80058718() != 0 || fn_8002460C() != 0) {
        HbHelpBar* h = (HbHelpBar*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = 1;
    }
}
