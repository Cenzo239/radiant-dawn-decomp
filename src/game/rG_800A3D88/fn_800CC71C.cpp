#include "game/rG_800A3D88/types.h"

// Five wrappers around fn_800CB69C that switch the current mode to table entry
// N for the duration of the call and then restore the previous one.

extern "C" {

extern void* lbl_803E7260[6];

void* fn_80077DB0(void*);
#if TARGET_PC
FE10_PROTO void fn_800CB69C(f32, f32, f32, f32, f32, int, int, int, p32arg, p32arg, p32arg, p32arg, p32arg);
#else
void fn_800CB69C(f32, f32, f32, f32, f32, int, int, int, int, int, int, int, int);
#endif

static inline int SwapMode(int idx) {
    void* old = fn_80077DB0(lbl_803E7260[idx]);
    int i;
    for (i = 0; i < 6; i++) {
        if (lbl_803E7260[i] == old) return i;
    }
    return -1;
}

#pragma use_lmw_stmw on
#define WRAP(name, idx)                                                                             \
    void name(f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, int a, int b, int c, int d, int e, int f, int g, int h) { \
        int prev = SwapMode(idx);                                                                   \
        fn_800CB69C(f1, f2, f3, f4, f5, a, b, c, d, e, f, g, h);                                    \
        if (prev == -1) prev = 0;                                                                   \
        SwapMode(prev);                                                                             \
    }

WRAP(fn_800CC71C, 0)
WRAP(fn_800CC8AC, 2)
WRAP(fn_800CCA3C, 3)
WRAP(fn_800CCBCC, 4)
WRAP(fn_800CCD5C, 5)
}
