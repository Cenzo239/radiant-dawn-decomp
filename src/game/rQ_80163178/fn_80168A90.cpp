/* fn_80168A90: round m1, exact (from equiv/fn_801689C8.cpp, sched: the two float-to-int conversions sat in
   each other's stack slot). The fix: the tile lookup is an inline `tA(int x, int y)` taking the floats as
   int arguments (arguments are evaluated last to first). fn_801689C8, the function before it, is exact in
   equiv/fn_801689C8.cpp. */
/* AI: proc steps that move the camera to the target tile (names guessed). */
#include "game/rQ_80163178/common.h"
extern "C" {
extern u8 lbl_804CB830;
extern u8 lbl_803CAB38[];
#if TARGET_PC
FE10_PROTO void fn_801030B8(Unit*, int, int, int, int, p32arg);
#else
void fn_801030B8(Unit*, int, int, int, int, void*);
#endif
void fn_800620A8(void*, f32, f32);
void fn_80083DC4(void*, int);

static inline BOOL IsM() { BOOL b = 1; u8 m = lbl_804CB830; if (m != 1 && m != 2) b = 0; return b; }
static inline u8 tA(int x, int y) { return lbl_803EC898.ter[2][(s8)x + (s8)y * 0x40]; }
void fn_80168A90(f32* p) {
    BOOL b = IsM();
    if (b && lbl_803CAB38[0x11] == 1 && tA(p[12], p[13]) == 0) {
        fn_80083DC4(p, 99);
        return;
    }
    fn_800620A8(lbl_803CAB38, p[12], p[13]);
}
}
