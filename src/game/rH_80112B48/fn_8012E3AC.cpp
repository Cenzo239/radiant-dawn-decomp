/* Support bit set, 8012E3AC. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
static inline void BitSet(u32* p, u32 k) {
    while (k >= 32) {
        k -= 32;
        p++;
    }
    *p |= 1 << k;
}
void fn_8012E3AC(Unit* u, int k) {
    if (k >= 0) {
        BitSet((u32*)((u8*)u + 0x2f0), k);
    }
}
}
