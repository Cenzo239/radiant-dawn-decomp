/* True when any inventory slot holds an item with the 0x40 flag set. */
#include "game/rH_80112B48/unit.h"
extern "C" {
BOOL fn_8012A9A4(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++, it++) {
        if (it->item && it->bit40) return 1;
    }
    return 0;
}
}
