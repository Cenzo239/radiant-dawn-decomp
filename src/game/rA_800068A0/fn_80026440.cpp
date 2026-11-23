/* Sets bit 3 on 2*n consecutive 16-bit cells starting at the object's
   current index (names guessed). */
#include "game/rA_800068A0/types.h"

struct Cells {
    u8 pad[0x20];
    u16 cell[0x40];  /* 0x20 */
    u8 pos;          /* 0xa0 */
};

extern "C" void fn_80026440(Cells* c, int n) {
    int i;
    for (i = 0; i < n * 2; i++) {
        c->cell[c->pos + i] |= 8;
    }
}
