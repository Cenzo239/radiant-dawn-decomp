/* Pair list: add an unordered pair (a, b) with a byte value unless present (at most 0x60). */
#include "game/rH_80112B48/types.h"
extern "C" {
struct Pr { void* a; void* b; u8 c; };
extern Pr lbl_80412C18[0x60];
extern int lbl_804CB80C;
void fn_80119BB4(void* a, void* b, u8 c) {
    /*P*/
    int i;
    Pr* e;
    void* t;
    int n;
    int r;
/*E*/
    n = lbl_804CB80C;
    e = lbl_80412C18;
    for (i = 0, r = 0; i < n; i++, e++) {
        t = e->a;
        if ((a == t && b == e->b) || (a == e->b && b == t)) {
            r = 1;
            break;
        }
    }
    if (!r && n < 0x60) {
        e = &lbl_80412C18[n];
        e->a = a;
        e->b = b;
        e->c = c;
        lbl_804CB80C++;
    }
}
}
