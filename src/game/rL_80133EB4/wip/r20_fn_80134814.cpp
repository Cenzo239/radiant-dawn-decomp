/* fn_80134814 (0x178, round 20): `other`. Complete and correct draft: resets the map-model environment state
 * (two 4-entry colour tables, fade colour, scroll and weather variables; names guessed). Compiles on its own.
 * What differs: 98 instructions against 94, all in one basic block. The template byte loads and every store are
 * the original's. The original keeps the constants 0, -0x5A, -1 and &lbl_804CB834 in saved registers loaded in the
 * prologue (stmw r24) and writes the three local colours to the stack at the very end; here the constants are
 * loaded late into volatile registers, the stack stores come right after the unrolled loop, and only r29..r31 are
 * saved (stw instead of stmw, hence the 4 extra instructions). Tried: static const colours (the loads then go
 * through `li base` and the stack copies vanish), the round 8 byte-local form in wip/near2.cpp, and the pragmas
 * opt_dead_assignments/opt_lifetimes/opt_propagation/opt_dead_code/scheduling/peephole off (no change or worse).
 */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw on
struct Clr { u8 r, g, b, a; };
extern "C" {
extern Clr lbl_80413BF8[4];
extern Clr lbl_80413BE8[4];
extern u8 lbl_804CB830;
extern Clr lbl_804CB834;
extern u8 lbl_804CB838, lbl_804CB839, lbl_804CB83A, lbl_804CB83B;
extern Clr lbl_804CB83C;
extern s16 lbl_804CB840, lbl_804CB842, lbl_804CB844;
extern s8 lbl_804CB846;
extern s16 lbl_804CB848, lbl_804CB84A;
extern u8 lbl_804CB84C, lbl_804CB84D, lbl_804CB84E, lbl_804CB84F, lbl_804CB850, lbl_804CB851, lbl_804CB852;

void fn_80134814(void) {
    Clr f = {0xFF, 0xFF, 0xFF, 0xFF};
    Clr a = {0x80, 0x80, 0x80, 0xFF};
    Clr b = {0xFF, 0xFF, 0xFF, 0xFF};
    int i;
    for (i = 0; i < 4; i++) {
        lbl_80413BF8[i] = a;
        lbl_80413BE8[i] = b;
    }
    lbl_804CB830 = 0;
    lbl_804CB834.r = 0;
    lbl_804CB834.g = 0;
    lbl_804CB834.b = 0;
    lbl_804CB834.a = 0;
    lbl_804CB839 = 0;
    lbl_804CB83A = 0;
    lbl_804CB83B = 0;
    lbl_804CB840 = -0x5A;
    lbl_804CB842 = 0;
    lbl_804CB844 = 0;
    lbl_804CB846 = -1;
    lbl_804CB848 = 0;
    lbl_804CB84A = 0;
    lbl_804CB838 = 0;
    lbl_804CB83C = f;
    lbl_804CB84C = 0;
    lbl_804CB84D = 0;
    lbl_804CB84E = 0;
    lbl_804CB84F = 0;
    lbl_804CB850 = 0;
    lbl_804CB851 = 0;
    lbl_804CB852 = 0;
}
}
