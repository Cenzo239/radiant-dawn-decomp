/* Talk/portrait windows: opens a face in the first free of the eight slots
   (names guessed). */
#include "game/rG_800A3D88/types.h"

extern "C" {
extern void* lbl_803E50D0[8];
void* fn_800C5EA4(int slot, const char* name, int x, int y, u32 flags, int z, int parent);

static inline int FreeSlot(void) {
    int i;
    for (i = 0; i < 8; i++) {
        if (lbl_803E50D0[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void* fn_800C6118(const char* name, int x, int y, u32 flags, int parent) {
    return fn_800C5EA4(FreeSlot(), name, x, y, flags, 0, parent);
}
}
