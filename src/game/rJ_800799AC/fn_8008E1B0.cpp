/* Sums (5 - level) over the type-7 traps inside the map's inner rectangle
   (names guessed). */
#include "game/rJ_800799AC/types.h"
#pragma use_lmw_stmw on

struct Trap { u8 pad[5]; u8 x5; };
extern "C" Trap* fn_80066130(void* list, s8 x, s8 y, u32 type);
extern "C" u8 lbl_803CB770[];
struct MapInfo { u8 pad[8]; s8 x0, y0, x1, y1; };
extern "C" MapInfo lbl_803EC898;

extern "C" int fn_8008E1B0(void) {
    int n = 0;
    int y, x;
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            Trap* t = fn_80066130(lbl_803CB770, x, y, 7);
            if (t != NULL) {
                n += 5 - t->x5;
            }
        }
    }
    return n;
}
