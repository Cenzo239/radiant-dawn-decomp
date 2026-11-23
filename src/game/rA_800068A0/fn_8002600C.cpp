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
u32 fn_8002607C(Seq* s, u32 code);

/* Appends an entry and writes a zero terminator after it. */
void fn_8002600C(Seq* s, u32 code, s16 val) {
    Ent* e;
    u8 c = fn_8002607C(s, code);
    e = &s->e[s->n];
    e->code = c;
    e->val = val;
    s->n++;
    e = &s->e[s->n];
    e->code = 0;
    e->val = 0;
}
}
