/* Bonus experience tally (names guessed): sum of the awards, and sum plus the
   amount carried over. */
#include "game/rJ_800799AC/types.h"

struct Tally {
    char names[8][0x20]; /* 0x000 */
    int vals[8];         /* 0x100 */
    int seen;            /* 0x120 */
    int n;               /* 0x124 */
    int base;            /* 0x128 */

    int sum() {
        int s = 0;
        int i;
        for (i = 0; i < n; i++) {
            s += vals[i];
        }
        return s;
    }
};

extern "C" {
int fn_8008DB58(Tally* t) {
    int s = 0;
    int i;
    for (i = 0; i < t->n; i++) {
        s += t->vals[i];
    }
    return s;
}

int fn_8008DC34(Tally* t) {
    return t->base + t->sum();
}
}
