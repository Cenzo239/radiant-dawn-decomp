#include "game/rB_8002E1C4/types.h"

/* map state, lbl_803EC898 */
typedef struct MapState {
    u8 pad[0xd];
    u8 grid[1][64 * 64]; /* per-tile byte layer, indexed x + y * 64 */
} MapState;
extern MapState lbl_803EC898;
extern u8 lbl_803E7320[];
#if TARGET_PC
FE10_PROTO void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, void *);
#else
void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, int mode);
#endif

void fn_8003B8B0(void* self, s8 x, s8 y)
{
    u8 v = lbl_803EC898.grid[0][x + y * 64];
    if (v == 0) return;
    fn_800CFC50(lbl_803E7320, x, y, v, 2);
}
