/* Sort comparator: true when b ranks below a by fn_80123BF0. */
#include "game/rH_80112B48/types.h"
extern "C" {
extern s16 fn_80123BF0(void*);
BOOL fn_8011EFC8(void* a, void* b) {
    int y = fn_80123BF0(b);
    int x = fn_80123BF0(a);
    return y < x;
}
}
