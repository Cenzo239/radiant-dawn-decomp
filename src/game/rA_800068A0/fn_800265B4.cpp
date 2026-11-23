/* Text/pad command list (names guessed): a list of up to 511 4-byte entries
   {code, pad, value} with a count, a mark, a "current group" pointer and a
   layout mode that swaps two blocks of the code translation. */
#include "game/rA_800068A0/types.h"

struct Ent { u8 code; u8 x1; s16 val; };
struct Seq {
    s16 n;          /* 0x000 */
    s16 mark;       /* 0x002 */
    Ent e[0x1ff];   /* 0x004 */
    Ent* cur;       /* 0x800 */
    u8 mode;        /* 0x804 */
};

extern "C" {
/* Assignment (operator=: returns the destination). */
Seq* fn_800265B4(Seq* d, const Seq* s) {
    int i;
    if (s == d) {
        return d;
    }
    d->n = s->n;
    d->mark = s->mark;
    d->mode = s->mode;
    d->cur = s->cur;
    for (i = 0; i < 0x1ff; i++) {
        d->e[i].code = s->e[i].code;
        d->e[i].x1 = s->e[i].x1;
        d->e[i].val = s->e[i].val;
    }
    return d;
}
}
